(function(){
    

    var XWIDTH = 32;
    var YWIDTH = 32;
    var ZWIDTH = 32;
    

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
        var index = y * XWIDTH * ZWIDTH + x * ZWIDTH + z;
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
    
    var GRASS = 1;
    var DIRT = 2;
    var WATER = 3;
    var STONE = 4;
    defineVoxel('Grass', 'grass_top.png', 'grass_side.png', 'dirt.png', false);
    defineVoxel('Dirt', 'dirt.png', 'dirt.png', 'dirt.png', false);
    defineVoxel('Water', 'water_still.png', 'water_still.png', 'water_still.png', true);
    defineVoxel('Stone', 'stone.png', 'stone.png', 'stone.png', false);
    
    noise.seed(Math.random());
    
    var xwidth = 5;
    var zwidth = 5;
    var height = 1;
    
    function createVolumes(fn){
        for (var i = 0; i < xwidth; i++) {
            for (var j = 0; j < height; j++) {
                for (var k = 0; k < zwidth; k++) {
                    var volume = new Volume(i, j, k);
                    fn(volume);
                    volume.send();
                }
            }
        }
    }
    
    createVolumes(function(volume){
        for (var x = 0; x < 32; x++) {
            for (var z = 0; z < 32; z++) {
                var y = Math.round(noise.perlin2(x/5,z/5) * 5 +16);
                volume.setVoxel(GRASS, x, y, z);
                y--;
                for(; y >= 0; y--){
                    if (y > 5) {
                        volume.setVoxel(DIRT, x, y, z);
                    } else {
                        volume.setVoxel(STONE, x, y, z);
                    }
                }
            }
        }
    });
//    
//    createVolumes(function(volume){
//       volume.setVoxel(GRASS, 0, 0, 0);
//       volume.setVoxel(GRASS, 0, 0, 1);
//       volume.setVoxel(GRASS, 0, 0, 2);
//       volume.setVoxel(GRASS, 0, 0, 3);
//       
//       volume.setVoxel(GRASS, 2, 0, 0);
//       volume.setVoxel(GRASS, 2, 0, 1);
//       volume.setVoxel(GRASS, 3, 0, 0);
//       volume.setVoxel(GRASS, 3, 0, 1);
//    });
    
})();