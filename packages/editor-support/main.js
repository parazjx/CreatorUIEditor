
/* jslint node: true, sub: true, esversion: 6 */
/* globals Editor */

"use strict";

const Fs = require('fs');
const Path = require('path');

const Electron = require('electron');

const TIMEOUT = -1;
const DEBUG_WORKER = true;
let PACKAGE_VERSION = '';

const Project = require('./core/Project');

let _buildState = 'sleep';

function _fetchVersion() {
    const Constants = require('./core/Constants');
    let info = Editor.Package.packageInfo(Editor.Package.packagePath(Constants.PACKAGE_NAME));
    PACKAGE_VERSION = info.version;
}

function _runWorker(url, message, project) {
    let buildWorker;
    Editor.App.spawnWorker(url, (worker) => {
        buildWorker = worker;
        let opts = {version: PACKAGE_VERSION, debug: DEBUG_WORKER};
        let state = project.dumpState();
        buildWorker.send(message, state, opts, (err) => {
            if (err) {
                Editor.error(err);
            }

            if (buildWorker) {
                buildWorker.close();
            }
            buildWorker = null;
        }, TIMEOUT);
    }, DEBUG_WORKER);
}

function _checkProject(opt) {
    let project = new Project(opt.profile);

    if (project.validate()) {
        return project;
    } else {
        if (opt.reason !== 'scene:saved') {
            Editor.Dialog.messageBox({
              type: 'warning',
              buttons: [Editor.T('MESSAGE.ok')],
              title: 'Warning - UIEditor',
              message: 'Please setup Export Path first',
              noLink: true,
            });
        } else {
            Editor.warn('[UIEditor] Please setup Export Path first');
        }
    }

    return null;
}

// opt = { reason: xxx, profile: yyy}
// 'profile' may be null
function _build(opt) {
    if (_buildState !== 'sleep' && _buildState !== 'finish') {
        Editor.warn('[UIEditor] Building in progress');
        return;
    }

    // called by `Build Now`
    if (opt === undefined) {
        const Constants = require('./core/Constants');
        let state = Editor.Profile.load('profile://project/elestorm-uieditor.json', Constants.PROFILE_DEFAULTS);
        opt = {
            profile: state.data
        }
    }

    let project = _checkProject(opt);
    if (!project) return;

    Editor.Ipc.sendToAll('elestorm-uieditor:state-changed', 'start', 0);

    let workerUrl = 'packages://elestorm-uieditor/core/BuildWorker';
    _runWorker(workerUrl, 'elestorm-uieditor:run-build-worker', project);
}

module.exports = {
    load() {
        _fetchVersion();
        Editor.log('[UIEditor] version ' + PACKAGE_VERSION);
    },

    unload() {
    },

    messages: {
        'setup-export-config'() {
            const Constants = require('./core/Constants');
            Editor.Panel.open(Constants.PACKAGE_NAME, {version: PACKAGE_VERSION});
        },

        'build'(event, opt) {
            _build(opt);
        },

        // can not recognize if the scene is modified
        'scene:saved'(event) {
            const Constants = require('./core/Constants');
            let state = Editor.Profile.load('profile://project/elestorm-uieditor.json', Constants.PROFILE_DEFAULTS);
            if (state.data.autoBuild) {
                _build({
                    reason: 'scene:saved',
                    profile: state.data});
            }
        },

        'elestorm-uieditor:state-changed'(event, state, progress) {
            _buildState = state;
            Editor.Ipc.sendToWins('elestorm-uieditor:state-changed', state, progress);
        }
    }
};

