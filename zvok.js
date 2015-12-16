$('#zvok1').popover({ trigger: "hover", html: true });
$('#zvok2').popover({ trigger: "hover", html: true });

$('#zvok1').on('click', function(){
  if(predvajanje != 1){
    predvajanje = 1;
    zvok(1);
  }
});

$('#zvok2').on('click', function(){
  if(predvajanje != 1){
    predvajanje = 1;
    zvok(2);
  }
});

function zvok(kanal){

  window.audioContext = new (window.AudioContext || window.webkitAudioContext)();
      
  var min = parseFloat(params.local.min_y);
  var max = parseFloat(params.local.max_y);

  var Nsignal = 1024;                      
  var fmin = 200;
  var fmax = 1200;
   
  var k = (fmax - fmin)/(Math.abs(max - min));
  var n = fmax - k*Math.abs(max);

  var frekvence = [];
  var fr;

  for (var i = 0; i < 1024; i = i+2){   // zracunaj sample

    fr = k*parseFloat(datasets[kanal - 1].data[i][1]) + n;
    fr = Math.round(fr*10000)/10000;

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
    
    if(i == 512){
      gain.gain.value = 0;
      predvajanje = 0;
      clearInterval(cs);
    }
    i++;

  }, 5);
}

<div id="btn_toolbar" class="col-xs-12">
  <div class="col-xs-8">
    <div class="col-xs-4">
      <div id="selzoompan" class="btn-group" data-toggle="buttons">
        <button id="btn_zoomin" class="btn btn-primary" onclick="selectTool.call(this, 'zoomin')">
        <span class="glyphicon glyphicon-zoom-in"></span>
        </button>
        <button id="btn_zoomout" class="btn btn-default" onclick="selectTool.call(this, 'zoomout')">
        <span class="glyphicon glyphicon-zoom-out"></span>
        </button>
        <button id="btn_pan" class="btn btn-default" onclick="selectTool.call(this, 'pan')" style="">
        <span class="glyphicon glyphicon-move"></span>
        </button>
      </div>
    </div>
    <div class="col-xs-4">
      <button id="btn_ch1" class="btn btn-primary" data-checked="true" onclick="setVisibleChannels(this)">Kanal 1</button>
      <button id="btn_ch2" class="btn btn-primary" data-checked="true" onclick="setVisibleChannels(this)">Kanal 2</button>
    </div>
    <div class="col-xs-4" style="padding-bottom: 0.5em;">
      <div class="col-xs-6">
        <button id="zvok1" style="background-color: white; border: none;" data-content="S klikom na ta gumb, se signal na zaslonu pretvori v zvočni signal z uporabo pretvorbe iz amplitude v frekvenco (amplitudno frekvenčna modulacija). To je eksperimentalni sistem, ki je namenjen slabovidnim ali slepim, ki jim ta način morda lahko olajša ali sploh omogoča sodelovanje pri eksperimentih. Sinusni signal se torej ne sliši kot zvok ene frekvence pač pa kot izmenjaje višji in nižji toni. <br><br> Aplikacija deluje smiselno, če graf na sliki miruje. To dosežemo z ustrezno nastavitvijo Proženja signala." data-placement="bottom">
        <img class="img-responsive" src="../assets/images/zvok_simbol_ch1.png" alt="zvok1" style="width: 100%;"/>
        </button>
      </div>
      <div class="col-xs-6">
        <button id="zvok2" style="background-color: white; border: none;" data-content="S klikom na ta gumb, se signal na zaslonu pretvori v zvočni signal z uporabo pretvorbe iz amplitude v frekvenco (amplitudno frekvenčna modulacija). To je eksperimentalni sistem, ki je namenjen slabovidnim ali slepim, ki jim ta način morda lahko olajša ali sploh omogoča sodelovanje pri eksperimentih. Sinusni signal se torej ne sliši kot zvok ene frekvence pač pa kot izmenjaje višji in nižji toni. <br><br> Aplikacija deluje smiselno, če graf na sliki miruje. To dosežemo z ustrezno nastavitvijo Proženja signala." data-placement="bottom">
        <img class="img-responsive" src="../assets/images/zvok_simbol_ch2.png" alt="zvok2" style="width: 100%;"/>
        </button>
      </div>
    </div>
  </div>
  <div class="col-xs-4"></div>
</div>
