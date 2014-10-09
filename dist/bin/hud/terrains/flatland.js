(function(){
    
    var GRASS = 1;
    var DIRT = 2;
    var WATER = 3;
    
    defineVoxel('Grass', 'grass_top.png', 'grass_side.png', 'dirt.png', false);
    defineVoxel('Dirt', 'dirt.png', 'dirt.png', 'dirt.png', false);
    defineVoxel('Water', 'water_still.png', 'water_still.png', 'water_still.png', false);  
    
    function Volume(x,y,z){
        this.position = {x:x,y:y,z:z};
        this.data = new ArrayBuffer(6 + 32*32*32);
        this.byteView = new Uint8Array(this.data);
        
        console.log(x + " " + y + " " + z);
        
        this.byteView[0] = (x & 0xFF00) >> 8
        this.byteView[1] = x & 0x00FF;
        
        this.byteView[2] = (y & 0xFF00) >> 8;
        this.byteView[3] = y & 0x00FF;
        
        this.byteView[4] = (z & 0xFF00) >> 8;
        this.byteView[5] = z & 0x00FF;
    }
    
    Volume.prototype.setVoxel = function(type, x, y, z){
        if (x >= 32 || y >= 32 || z >= 32) {
            throw "Max coordinate is 32";
        }
        var index = 6 + x * 32 * 32 + y * 32 + z;
        if (index >= this.data.length) {
            throw "Set Voxel Out of Bounds";
        }
        this.byteView[index] = type;        
    };
    
    Volume.prototype.send = function(){
        var xhr = new XMLHttpRequest();
        xhr.open("POST", "http://voxels", true);
        xhr.send(this.byteView);
    };
    
    


    function clear(){
        volumeSendQueue = [];
        v = 0;
        clearVoxels();
    }
    
    clear();
    for (var i = 0; i < 10; i++) {
        for (var j = 0; j < 2; j++) {
            for (var k = 0; k < 10; k++) {
                var volume = new Volume(i, j, k);
                for (var x = 0; x < 32; x++) {
                    for (var y = 0; y < 32; y++) {
                        for (var z = 0; z < 32; z++) {
                            if(j == 0){
                                volume.setVoxel(DIRT, x, y, z);
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