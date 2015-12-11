    $('#zvok').on('click', function(){

      $('#zvok').attr("disabled", true);

      //var audioContext = new (window.AudioContext || window.webkitAudioContext)();

      window.audioContext = new (window.AudioContext || window.webkitAudioContext)();
        
      var t = [];
      var min = 0;
      var max = 0;

      for(var i = 0; i < 1024; i++){

        t.push(datasets[0].data[i]);

        if(t[i] < min){
          min = t[i];
        }
        if(t[i] > max){
          max = t[i];
        }
      }

      var Nsignal = 1024;                      
      var fmin = 200;
      var fmax = 1200;
       
      var k = (fmax - fmin)/(max - min);
      var n = fmax - k*max;

      var z = 0.00; 
      var časi = [];
      var frekvence = [];
      var fr;

      for (var i = 0; i < 1024; i++){

        fr = k*t[i]+n;
        fr = Math.round(fr);

        z = Math.round((z + 0.05)*100)/100;
      
        časi.push(z);
        frekvence.push(fr);
      }

      var oscillator = window.audioContext.createOscillator();
      var gain =  window.audioContext.createGain();
      gain.gain.value = 1;

      oscillator.connect(gain);
      gain.connect(window.audioContext.destination);
      oscillator.noteOn(0);

      var i = 0;

      var cs = setInterval( function(){

        oscillator.frequency.value = frekvence[i];
        console.log(frekvence[i]);

        if(i == 1024){
          gain.gain.value = 0;
          oscillator.noteOff();
          clearInterval(cs);
        }
        i++;

      }, 5);

      /*
      window.updateSig = function(freq, z, k){

        oscillator.frequency.value = freq;
        oscillator.connect(audioContext.destination);
        oscillator.start(audioContext.currentTime + z);
        oscillator.stop(audioContext.currentTime + z + k);

        if(z - 4 > 1 && z > 4 && z < 6 && !isNaN(z) && isFinite(z)){
          $('#zvok').attr("disabled", false);
        }
      };

      var t = datasets[0].data.slice();
      var min = 0;
      var max = 0;

      for(var i = 0; i < 1024; i++){

        t[i][1] = t[i][1]*100;
        
        if(t[i][1] < min){
            min = t[i][1];
        }
        if(t[i][1] > max){
          max = t[i][1];
        }
      }

      var fmin = 400;
      var fmax = 2000;
       
      var k = (fmax - fmin)/(max - min);
      var n = fmax - k*max;

      var z = 0; 
      var fr = 0;

      var oscillator = audioContext.createOscillator();
      oscillator.type = 'sine';
      
      for (var i = 0; i < 1024; i = i + 10){

        fr = k*t[i][1] + n;
        fr = Math.round(fr);

        z = z + 0.04;
      
        window.updateSig(fr, z, 0.04);    //predvajanje
      }*/
  });