(function(){
    
    var DIRT = 1;
    
    function Volume(x,y,z){
        this.position = {x:x,y:y,z:z};
        this.data = new ArrayBuffer(3 + 32*32*32);
        this.byteView = new Uint8Array(this.data);
        this.byteView[0] = x;
        this.byteView[1] = y;
        this.byteView[2] = z;
    }
    
    Volume.prototype.setVoxel = function(type, x, y, z){
        if (x >= 32 || y >= 32 || z >= 32) {
            throw "Max coordinate is 32";
        }
        var index = 3 + x * 32 * 32 + y * 32 + z;
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
    
    
    var volumeSendQueue = [];
    
    function startVolumeLoop(){
        if(window.volumeLoop){
            clearInterval(window.volumeLoop);
        }
        window.volumeLoop = setInterval(function(){
            for(var i = 0; i < volumeSendQueue.length; i++){
                var volume = volumeSendQueue[i];
                volume.send();
            }
            volumeSendQueue = [];
        }, 100);
    }
    
    var v = 0;
    
    function startCreateVolumesLoop(){
        if(window.createVolumesLoop){
            clearInterval(window.createVolumesLoop);
        }
        window.createVolumesLoop = setInterval(function(){
            if(v > 0){
                return;
            }
            var volume = new Volume(v / 20, 0, v % 20);
            for (var x = 0; x < 32; x++) {
                for (var y = 0; y < 1; y++) {
                    for (var z = 0; z < 32; z++) {
                        volume.setVoxel(DIRT, x, y, z);
                    }
                }
            }
            volumeSendQueue.push(volume);
            v++;
        }, 200);
    }
    
    function clear(){
        volumeSendQueue = [];
        v = 0;
        clearVoxels();
    }
    
    clear();
    startVolumeLoop();
    startCreateVolumesLoop();
})();