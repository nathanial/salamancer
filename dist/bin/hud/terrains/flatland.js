(function(){
    
    var GRASS = 1;
    var DIRT = 2;
    var WATER = 3;
    var STONE = 4;
    var XWIDTH = 32;
    var YWIDTH = 32;
    var ZWIDTH = 32;
    
    defineVoxel('Grass', 'grass_top.png', 'grass_side.png', 'dirt.png', false);
    defineVoxel('Dirt', 'dirt.png', 'dirt.png', 'dirt.png', false);
    defineVoxel('Water', 'water_still.png', 'water_still.png', 'water_still.png', true);  
    defineVoxel('Stone', 'stone.png', 'stone.png', 'stone.png', false);
    
    function Volume(x,y,z){
        this.position = {x:x,y:y,z:z};
        this.data = [];
        for(var i = 0; i < XWIDTH * YWIDTH * ZWIDTH; i++){
            this.data[i] = 0;
        }
    }
    
    Volume.prototype.setVoxel = function(type, x, y, z){
        if (x >= XWIDTH || y >= YWIDTH || z >= ZWIDTH) {
            throw "Max coordinate is 32";
        }
        var index = x * XWIDTH * YWIDTH + y * ZWIDTH + z;
        if (index >= this.data.length) {
            throw "Set Voxel Out of Bounds";
        }
        this.data[index] = type;
    };
    
    Volume.prototype.send = function(){
        var rle = this.runLengthEncoding();
        createVoxels(this.position.x, this.position.y, this.position.z, rle);
    };
    
    Volume.prototype.runLengthEncoding = function(){
        this.cursor = 0;
        var runs = [];
        while(this.cursor < this.data.length){
            runs.push(this.nextRun());
        }
        return runs.join(",");
    };
    
    Volume.prototype.nextRun = function(){
        var type = this.data[this.cursor];
        var count = 0;
        while(this.cursor < this.data.length && this.data[this.cursor] === type){
            count++;
            this.cursor++;
        }
        return count+":"+type;
    };
    
    function clear(){
        volumeSendQueue = [];
        v = 0;
        clearVoxels();
    }
    
    clear();
    var xwidth = 20;
    var zwidth = 10;
    var height = 3;
    
    for (var i = 0; i < xwidth; i++) {
        for (var j = 0; j < height; j++) {
            for (var k = 0; k < zwidth; k++) {
                var volume = new Volume(i, j, k);
                for (var x = 0; x < 32; x++) {
                    for (var y = 0; y < 32; y++) {
                        for (var z = 0; z < 32; z++) {
                            if(j == 0 || i == 0 || i == xwidth - 1 || k == 0 || k == zwidth - 1){
                                volume.setVoxel(STONE, x, y, z);
                            } else {
                                volume.setVoxel(WATER, x, y, z);
                            }
                        }
                    }
                }
                volume.send();
            }
        }
    }
})();