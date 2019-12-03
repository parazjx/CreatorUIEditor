
/* jslint node: true, sub: true, esversion: 6 */
/* globals Editor */

"use strict";

const Fs = require('fire-fs');
const Path = require('path');

const printlog = Editor ? Editor.log : console.log;
function tostring(v) {
    return v === null ? '' : v.toString();
}

module.exports = class Project {
    constructor(state) {
        this.path = state ? state.path : '';
        this.autoBuild = state ? state.autoBuild : true;
        this.hasTryMake = false;
    }

    validate() {
        if (typeof this.path !== 'string' || this.path === '') {
            Editor.warn('[UIEditor] not set Export Path');
            return false;
        }

        try {
            let stat = Fs.statSync(this.path);
            if (!stat.isDirectory()) {
                Editor.warn('[UIEditor] ' + this.path + ' is not directory');
                return false;
            }
        } catch (e) {

            if (!this.hasTryMake) {
                Fs.mkdirSync(this.path);

                Editor.log("outpath", this.path);

                this.hasTryMake = true;
                return this.validate();
            }
            
            Editor.warn('[UIEditor] invalid path: ' + this.path);
            return false;
        }

        return true;
    }

    printlog() {
        printlog('-- dump project');
        printlog('  path: ' + tostring(this.path));
        printlog('  autoBuild: ' + (this.autoBuild ? 'YES' : 'NO'));
    }

    dumpState(state) {
        if (!state) {
            state = {};
        }
        state.path = this.path;
        state.autoBuild = this.autoBuild;
        return state;
    }
};
