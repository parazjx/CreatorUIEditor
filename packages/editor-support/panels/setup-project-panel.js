
/* jslint node: true, sub: true, esversion: 6, browser: true */
/* globals Editor */

'use strict';

const Fs = require('fs');
const Path = require('path');
const Electron = require('electron');

const Project = require(Editor.url('packages://elestorm-uieditor/core/Project.js'));
const Constants = require(Editor.url('packages://elestorm-uieditor/core/Constants.js'));

const styleUrl = Editor.url('packages://elestorm-uieditor/panels/style.css');
const style = Fs.readFileSync(styleUrl);

const templateUrl = Editor.url('packages://elestorm-uieditor/panels/setup-project-panel.html');
const template = Fs.readFileSync(templateUrl);

Editor.Panel.extend({
    style: style,
    template: template,

    ready() {
        let opts = Editor.require('packages://elestorm-uieditor/package.json');

        let profileProject = this.profiles.project;
        if (profileProject.data.path.length == 0) {
            profileProject.data.path = Constants.EXPORT_DIR;
            profileProject.save();
        }

        let vm;
        window.vm = vm = this._vm = new window.Vue({
            el: this.shadowRoot,
            data: {
                profileProject: profileProject,
                task: '',
                buildState: 'sleep',
                buildProgress: 0,
                version: opts.version
            },

            watch: {
                project: {
                    handler(val) {
                        if (!profileProject.save) return;

                        profileProject.save();
                    },
                    deep: true
                }
            },

            methods: {
                _onChooseDistPathClick(event) {
                    event.stopPropagation();
                    let res = Editor.Dialog.openFile({
                        defaultPath: this.profileProject.data.path,
                        properties: ['openDirectory']
                    });
                    if (res && res[0]) {
                        this.profileProject.data.path = res[0];
                        this.profileProject.save();
                    }
                },

                _onShowInFinderClick(event) {
                    event.stopPropagation();
                    if (!Fs.existsSync(this.profileProject.data.path)) {
                        Editor.warn('%s not exists!', this.profileProject.data.path);
                        return;
                    }
                    Electron.shell.showItemInFolder(this.profileProject.data.path);
                    Electron.shell.beep();
                },

                _onBuildClick(event) {
                    event.stopPropagation();
                    Editor.Ipc.sendToMain('elestorm-uieditor:build', {
                        reason: 'ui',
                        profile: this.profileProject.data
                    });
                },

                _onSetupClick(event) {
                    event.stopPropagation();
                    Editor.Panel.close('elestorm-uieditor');
                },

                _onChangeExportResourceOnly(event) {
                    event.stopPropagation();
                    this.profileProject.data.exportResourceOnly = event.target.value;
                    this.profileProject.save();
                },

                _onChangeExportDynamicallyLoadResource(event) {
                    event.stopPropagation();
                    this.profileProject.data.exportResourceDynamicallyLoaded = event.target.value;
                    this.profileProject.save();
                },

                _onChangeAutoBuild(event) {
                    event.stopPropagation();
                    this.profileProject.data.autoBuild = event.target.value;
                    this.profileProject.save();
                }
            }
        });
    },

    _stateChanged: function(state, progress) {
        this._vm.buildProgress = progress;
        this._vm.buildState = state;
    },

    messages: {
        'elestorm-uieditor:state-changed'(event, state, progress) {
            this._stateChanged(state, progress);
        }
    }
});

