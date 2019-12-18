const fs = require('fs');
const fire_fs = require('fire-fs');
const path = require('path');
const Utils = require('../Utils');
const Constants = require('../Constants');
const Scene = require('./Scene');
const state = require('./Global').state;
const get_sprite_frame_name_by_uuid = require('./Utils').get_sprite_frame_name_by_uuid;

let uuidInfos = null;

/**
 * bootstrap + helper functions
 */
class FireParser {
    constructor() {
        this._state = state;
        this._json_file = null;
        this._json_output = {version: Constants.VERDION, root: {}};
        this._creatorassets = null;
    }

    to_json_setup() {
        // this.to_json_setup_design_resolution();
        this.to_json_setup_sprite_frames();
        // this.to_json_setup_collision_matrix();
    }

    to_json_setup_sprite_frames() {
        let sprite_frames = [];

        for (let sprite_frame_uuid in state._sprite_frames) {
            let sprite_frame = state._sprite_frames[sprite_frame_uuid];

            let frame = {
                name: get_sprite_frame_name_by_uuid(sprite_frame_uuid),
                texturePath: state._assetpath + sprite_frame.texture_path,
                rect: {x:sprite_frame.trimX, y:sprite_frame.trimY, w:sprite_frame.width, h:sprite_frame.height},
                offset: {x:sprite_frame.offsetX, y:sprite_frame.offsetY},
                rotated: sprite_frame.rotated,
                originalSize: {w:sprite_frame.rawWidth, h:sprite_frame.rawHeight}
            };
            // does it have a capInsets?
            if (sprite_frame.borderTop != 0 || sprite_frame.borderBottom != 0 || 
                sprite_frame.borderLeft != 0 || sprite_frame.borderRgith != 0) {
                
                frame.centerRect = {
                    x: sprite_frame.borderLeft,
                    y: sprite_frame.borderTop,
                    w: sprite_frame.width - sprite_frame.borderRight - sprite_frame.borderLeft,
                    h: sprite_frame.height - sprite_frame.borderBottom - sprite_frame.borderTop
                }
            }

            // single png, but not plist or pvr
            if (frame.texturePath.endsWith(frame.name)) {
                sprite_frames.push(frame);    
            }
            
        }

        this._json_output.spriteFrames = sprite_frames;
    }

    create_file(filename) {
        fire_fs.ensureDirSync(path.dirname(filename));
        return fs.openSync(filename, 'w');
    }

    convertSceneToNode (rtData) {
        if (rtData.children) {
            let canvas = rtData.children[0];
            if (canvas.object) {
                canvas.object.name = "root";
                canvas.object.position.x = 0;
                canvas.object.position.y = 0;
                canvas.object.contentSize.w = 0;
                canvas.object.contentSize.h = 0;
                return canvas;
            } 
        }
            
        return {
            "object": {
                "enabled": true,
                "name": "root",
                "anchorPoint": {
                    "x": 0.5,
                    "y": 0.5
                },
                "position": {
                    "x": 0,
                    "y": 0
                },
                "contentSize": {
                    "w": 0,
                    "h": 0
                },
            },
            "object_type": "Node",
            "children": []
        }
    }

    run(sceneID, filename, assetpath, path_to_json_files) {
        state._filename = path.basename(filename, '.fire');
        let sub_folder = path.dirname(filename).substr(Constants.ASSETS_PATH.length + 1);
        let outpath = path.join(path_to_json_files, sub_folder);
        
        state._assetpath = assetpath;

        state._json_data = JSON.parse(fs.readFileSync(filename));

        state._json_data.forEach(obj => {
            if (obj.__type__ === 'cc.SceneAsset') {
                let scene = obj.scene;
                let scene_idx = scene.__id__;
                let scene_dat = state._json_data[scene_idx];

                if (sceneID === scene_dat._id) {

                    let scene_obj = new Scene(scene_dat);
                    scene_obj.parse_properties();

                    this.to_json_setup();
                    let jsonNode = scene_obj.to_json(0, 0);
                    let rootNode = this.convertSceneToNode(jsonNode);

                    if (rootNode.children && rootNode.children.length > 0) {

                        let rootjson = JSON.parse(JSON.stringify(this._json_output))

                        for (var i = 0; i < rootNode.children.length; i++) {
                            let node = rootNode.children[i];
                            
                            if (node.object_type !== "Node") {
                                Editor.error("Only Support Node! Hang up " + node.object.node.name + " to a parent node!");
                                continue;
                            }

                            if (node.object.name !== 'Main Camera') {

                                Editor.success("Export Success:", node.object.name);

                                let filename = path.join(outpath, node.object.name)+'.json';
                                rootjson.root = node;
                                this.writeNodeDataToJson(rootjson, filename);
                            } else {
                                if (rootNode.children.length === 1) {
                                    Editor.info("Cannot find any node in scene:", state._filename);
                                }
                            }
                        };

                    } else {
                        Editor.info("Cannot find any node in scene: ", state._filename);
                    }
                }
            }
        });
    }

    writeNodeDataToJson (jsData, filename) {
        let file = this.create_file(filename);
        let dump = JSON.stringify(jsData, null, '\t').replace(/\\\\/g,'/');
        fs.writeSync(file, dump);
        fs.close(file);
    }


}

function parse_fire(sceneID, filenames, assetpath, path_to_json_files, uuidmaps) {
    if (assetpath[-1] != '/')
        assetpath += '/';

    uuidinfos = uuidmaps;

    let uuid = {};
    filenames.forEach(function(filename) {
        state.reset();
        let parser = new FireParser();
        parser.run(sceneID, filename, assetpath, path_to_json_files)
        for(let key in state._uuid) {
            if (state._uuid.hasOwnProperty(key))
                uuid[key] = state._uuid[key];
        }
    });
    return uuid;
}

module.exports = parse_fire;