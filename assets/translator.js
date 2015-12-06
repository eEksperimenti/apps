$( document ).ready(function() {
    //CHANGE HERE: //////////////////////////////////////////////////
    var baseLanguage='sl'; //jezik, v katerem so originalni napisi
    var translations=
    [
		{'sl':'Samodejna nastavitev merilnih območij','en':'Autoscale'},
		{'sl':'Napetostnega in časovnega','en':'AUTOSCALE'},
        {'sl':'Kanal','en':'Channel'},
        {'sl':'Povprečenje signalov','en':'Averaging'},
        {'sl':'Ponastavi','en':'Reset zoom'},
		{'sl':'Zunanji izvor','en':'External'},
		{'sl':'Izvor prožilnega signala','en':'Source'},
		{'sl':'Način proženja','en':'Mode'},
		{'sl':'Enkratno proženje','en':'Single '},
		{'sl':'Enkratno','en':'Single'},
		{'sl':'Običajno','en':'Normal'},
		{'sl':'Ponavljajoče','en':'Continuous'},
		{'sl':'Samodejno','en':'Auto'},
		{'sl':'Prehod signala za proženje','en':'Edge'},
		{'sl':'Pozitiven prehod','en':'Rising'},
		{'sl':'Negativen prehod','en':'Falling'},
		{'sl':'Prag proženja','en':'Level'},
		{'sl':'Širina','en':'Range '},
		{'sl':'Ročna nastavitev merilnih območij','en':'Range'},
		//{'sl':'','en':'Range'},
		{'sl':'Časovno merilno območje','en':'X axis'},
		{'sl':'Napetostno merilno območje','en':'Y axis'},
		{'sl':'Premik','en':'Offset'},
		{'sl':'Prikaz signalnih parametrov','en':'Measure'},
		{'sl':'Najmanjša napetost','en':'Min'},
		{'sl':'Največja napetost','en':'Max'},
		//{'sl':'Vršna napetost (Vpp)','en':'Amp (Vpp)'},
		{'sl':'Spektralni analizator','en':'Spectrum Analyzer'},
		{'sl':'Zadrži sliko kanala 1','en':'Freeze Ch1'},
		{'sl':'Zadrži sliko kanala 2','en':'Freeze Ch2'},
		{'sl':'Frekvenčni razpon','en':'Freq. range'},
		{'sl':'Največja spektralna moč na kanalu 1','en':'Peak Ch1'},
		{'sl':'Največja spektralna moč na kanalu 2','en':'Peak Ch2'},
		{'sl':'Povprečna napetost','en':'Avg'},
		{'sl':' Frekvenca','en':'Frequency'},
		{'sl':'Frekvenca','en':'Freq'},
		{'sl':'Perioda','en':'Period'},
		{'sl':'Merilni sondi','en':'Gain settings'},	
		{'sl':'Signalni generator in osciloskop','en':'Generator & Oscilloscope'},
		{'sl':'Signalni generator','en':'Signal generator'},
		{'sl':'Nastavitev ojačanja','en':'Gain setting'},
		{'sl':'Faktor slabljenja','en':'Probe attenuation'},
		{'sl':'Oblika izhodnega signala','en':'Signal type'},
		{'sl':'Vzorčni signali','en':'Example signals'},
		{'sl':'Sinusna','en':'Sine'},
		{'sl':'Pravokotna','en':'Square'},
		{'sl':'Trikotna','en':'Triangle'},
		{'sl':'Iz datoteke','en':'From file'},
		{'sl':' Vršna napetost','en':'Amplitude'},
		{'sl':'Enosmerna komponenta','en':'DC offset'},
		{'sl':'Način proženja','en':'Trigger mode'},
		{'sl':'Naloži datoteko','en':'File upload'},
		{'sl':'Proženje','en':'Trigger'},
		{'sl':'Čas','en':'Time'},
		{'sl':'Vršna napetost','en':'Amp'},
		{'sl':'Napetostnega','en':'AUTO'},
		{'sl':'Napetost','en':'Voltage'},
		{'sl':'Jezik','en':'Language'},
		{'sl':'Spektralna moč','en':'Power'},
		{'sl':'','en':''},
    ];
    ///////////////////////////////////////////////////
    function translator(fromLang,toLang,el)
    {
        if (toLang===undefined || toLang=='') toLang=baseLanguage;
        if (fromLang===undefined || fromLang=='') fromLang=baseLanguage;
        
        var selection;
        if (el===undefined)
            selection=$('body *');
        else
            selection=$(el);
            
        selection.contents().filter(function() { 
            if (this.nodeType == 3)
            {
                for (var i=0;i<translations.length;++i)
                {
                    this.nodeValue=this.nodeValue.replace(translations[i][fromLang],translations[i][toLang]);
                }
            }
        });
    }
   translator(baseLanguage,location.hash.substr(1, 2));
    $('.translate').click(function(){translator(location.hash.substr(1, 2),$(this).attr('href').substr(1, 2))});
    $('body *').on("translate",function(){translator(baseLanguage,location.hash.substr(1, 2),this)});
});