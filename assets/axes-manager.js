(function (window, document, undefined) {
	(function() {

	    var proxied = $.plot;
	    $.plot = function() {
		
			var args = Array.prototype.slice.call(arguments);
			
			if(am.yaxis2 == true){

				if (y2.element==null){

					var y2element = $('<div id="' + y2.title_id + '" class="y2title" style="display: block; color: rgb(197, 29, 34); overflow: hidden; white-space: nowrap; width: 15em;"></div>');
					args[0].parent().append(y2element);
					y2.element=y2element;
				}
				
				if (args[2] === undefined) args[2] = {};
				
				var options = args[2];

				if (options.yaxes === undefined) options.yaxes = [{},{}];

				options.yaxes[1].position = 'right';
				options.yaxes[1].alignTicksWithAxis = y2.alignTicksWithAxis.prop("checked")?1:0;
				
				am.initContainer(y2);
				am.update();
				am.updateLabels();
			}

			am.plot = proxied.apply(this, args);//call the default is here
			$('#y2title,.y2title').css('left',(am.plot.getPlaceholder().parent().width() + 10) + 'px')
			
			var _setupGrid = am.plot.setupGrid;

		    am.plot.setupGrid = function(){

				var data = am.plot.getData();

				if (am.yaxis1 == false) data[0].lines.show = false;
				if (am.yaxis2 == false && (data.length == 2 || data.length == 3)) data.splice(1,1);
				if (am.yaxis2 && data[1] !== undefined) data[1].yaxis = 2
					
				//////////////////////////
				var len=data[0].data.length;
				var m1=eval(y1.faktor);
				var m2=eval(y2.faktor);

				for (var i=0;i<len;++i) {

					var va=data[0].data[i][1];
					var vb=0.0;

					if (am.yaxis2 && data[1] !== undefined) vb = data[1].data[i][1];

					data[0].data[i][1]=m1[0]*va+m1[1]*vb+m1[2];

					if (am.yaxis2 && data[1] !== undefined) data[1].data[i][1] = m2[0]*va+m2[1]*vb+m2[2];
				}
					
				var options=am.plot.getOptions();
				options.yaxes[0].min = y1.ymin;
				options.yaxes[0].max = y1.ymax;
				
				if (am.yaxis2 && data[1]!==undefined){

					options.yaxes[1].min = y2.ymin;
					options.yaxes[1].max = y2.ymax;
					options.yaxes[1].alignTicksWithAxis = y2.alignTicksWithAxis.prop("checked")?1:0;
				}
					
				////////////////////////

				am.plot.setData(data);
				var rval=_setupGrid.apply(this,arguments);

				if (am.yaxis1==false) {

					$('.legend td:eq(1)').remove();
					$('.legend td:first').remove();
				}

		      return rval;
		    }
		
			return am.plot;
		};

	    $.plot.plugins = proxied.plugins;
	})();
	
    var oldam = window.am,
    am = {};
    am.version = '1.0.0';

    // define am for Node module pattern loaders, including Browserify
    if (typeof module === 'object' && typeof module.exports === 'object') {
            module.exports = am;
    
    // define as AMD module
    } else if (typeof define === 'function' && define.amd) {
            define(am);
    }
    
    // define as a global am variable, saving the original am to restore later if needed
    
    am.noConflict = function () {

        window.am = oldam;
        return this;
    };
    
    window.am = am;
    
	am.div_id1 = 'nastavitve1';
	am.div_id2 = 'nastavitve2';
	am.div_id3 = 'nastavitve3';

	am.yaxis1 = true;
	am.yaxis2 = true;

    var y = {'id':'',title_id:'','velicina':'','enota':'','faktor': '[1, 0, 0]', 'ymin':-1,'ymax':1}
    var y1 = $.extend(true, {}, y);
	var y2 = $.extend(true, {}, y);

	y2.faktor = '[0,1,0]';
	y1.id = 'y1';
    y2.id = 'y2';
	y1.title_id = 'ytitle';
    y2.title_id = 'y2title';

    function preberi(file){
	    
		$.get(file,function(txt){

	    	var lines = txt.split("\n");
		   
		    y1["faktor"] = lines[63].split(":")[1];
		    y2["faktor"] = lines[68].split(":")[1];

		    y1["ymin"] = lines[64].split(":")[1];
		    y1["ymax"] = lines[65].split(":")[1];

		    y2["ymin"] = lines[69].split(":")[1];
		    y2["ymax"] = lines[70].split(":")[1];

		    y1["velicina"] = lines[61].split(":")[1];
		    y1["enota"] = lines[62].split(":")[1];

		    y2["velicina"] = lines[66].split(":")[1];
		    y2["enota"] = lines[67].split(":")[1];

		});
    }

    var src = (window.location).toString();
    var tezavnost = src.substring(src.lastIndexOf("#") + 1);

    var remote = src.indexOf("ugotoviElement");

    if(remote != -1){

   		preberi("default_params.txt");
    }
    else if(tezavnost == "lahko" && remote == -1){
      
   		preberi("default_params.txt");
	}
    
    function extractUnitFromLabel(label)
    {
			return label.substring(label.lastIndexOf("[") + 1,label.lastIndexOf("]"));
    }
    
    addElement=function(y){

		if (y.title_id == null) return;
		
		var element = $('#' + y.title_id);
		
		if (element.length == 0){

			element = $('.' + y.title_id).first();

			if (element.length == 0) element = null; 
		}
		y.element = element;
    }
    
	am.update_yrange = function(rinx,ymin,ymax){

		var yax = y1;

		if (rinx == 1) yax = y2;

		yax.ymin = ymin;
		yax.ymax = ymax;

		am.update();
	}
		
    am.init=function(){

		if (am.yaxis2==false) y2.title_id=null;
		
		var html = "<form role='form' class='nastavitve'>\
				<div class='form-group '>\
				  <label for='velicina-y%1'> Veličina </label>\
				  <input type='text' class='form-control' id='velicina-y%1'>\
				</div>\
				<div class='form-group'>\
				  <label for='enota-y%1'> Enota </label>\
				  <input type='text' class='form-control' id='enota-y%1'>\
				</div>\
				<div class='form-group'>\
				  <label for='faktor-y%1'>Faktor pretvorbe [a%1,b%1,c%1] (a%1*V1+b%1*V2+c%1)</label>\
				  <input type='text' class='form-control' id='faktor-y%1'>\
				</div>\
				<div class='form-group'>\
				  <label for='ymin-y%1'>y<sub>min</sub></label>\
				  <input type='text' class='form-control' id='ymin-y%1'>\
				</div>\
				<div class='form-group'>\
				  <label for='ymax-y%1'>y<sub>max</sub></label>\
				  <input type='text' class='form-control' id='ymax-y%1'>\
				</div>\
			</form>";
		
		var cb='<div class="checkbox">\
			<label>\
				<input type="checkbox" id="alignTicksWithAxis" value="" checked>\
					poravnaj oznake obeh ordinat\
			</label>\
			</div>';

		var y_S1 = '<a data-toggle="collapse" data-target="#';

		// vmes dodaj id

		var y_S2 = '" style="color: black; text-decoration: none; cursor: pointer;">\
                    <div class="panel panel-heading" style="background-color: rgb(242, 242, 242);">\
                      <h4 class="panel-title">';

        // vmes dodaj naslov        

        var y_S3 =  '</h4></div></a><div class="panel-collapse collapse" id="';

        // vmes dodaj id

        var y_S4 = '"><div class="panel-body" style="border: none;">';
        
        // vmes dodaj inpute

        var y_S5 = '</div></div>';                

		$('#' + am.div_id1).html( y_S1 + "levaY" + y_S2 + "leva Y os" + y_S3 + "levaY" + y_S4 + '<div class="checkbox"><label><input type="checkbox" class="axis-toggler" id="left-axis" value="" checked><b>Leva Y os (ordinata)</b></label></div>' + html.replace(/%1/g, '1') + y_S5);
		
		$('#' + am.div_id2).html( y_S1 + "desnaY" + y_S2 + "desna Y os" + y_S3 + "desnaY" + y_S4 + '<div class="checkbox"><label><input type="checkbox" class="axis-toggler" id="right-axis" value="" checked><b>Desna Y os (ordinata)</b></label></div>'+html.replace(/%1/g, '2') + y_S5);

		$('#' + am.div_id3).html(cb);

		$('#y2title,.y2title').css('right','0');

		$('.nastavitve > .form-group > .form-control').keypress(function(event){
			
			if (event.which == 13){

				am.update(true);
				am.updateLabels();
			}
		});

		$('.nastavitve > .form-group > .form-control').on("blur", function(){
			
			am.update(true);
			am.updateLabels();

		});
		
		$.each([y1,y2], function(index, value) {addElement(value)});
		$.each([y1,y2], function(index, value) {am.initContainer(value)});

		y2.velicina = y1.velicina;
		y2.enota = y1.enota;

		y2.alignTicksWithAxis = $('#alignTicksWithAxis');
		am.update();

	  	$('.axis-toggler').click(function(){

			var cb=$(this);

			if (cb.attr('id')=='left-axis'){

				am.yaxis1=cb.prop("checked");

				if (!am.yaxis1){

					$('#'+y1.title_id).hide();

					var gh1 = $('.graph-holder:first').position().top;
					var tc1 = $('#trigger_canvas').parent().position().left;

					$('.leftZoom').hide();

					var gh2 = $('.graph-holder:first').position().top;
					var tc2 = $('#trigger_canvas').parent().position().left;

					$('#trigger_canvas').parent().css('left',(tc1-tc2)+'px');
					$('.graph-holder:first').parent().css('top',(gh1-gh2)+'px');
					$('.rightZoom:first').css('top',(300-(gh1-gh2))+'px');
				}
				else {
					$('#'+y1.title_id).show();
					$('.graph-holder:first').parent().css('top',0);
					$('#trigger_canvas').parent().css('left',0);
					$('.rightZoom:first').css('top','300px');
					$('.leftZoom').show();
				}
			}
			else if (cb.attr('id')=='right-axis'){

				am.yaxis2=cb.prop("checked");

				if (!am.yaxis2){

					am.y2Axis=$('.y2Axis');
					am.y2Axis.remove();
					$('#'+y2.title_id).hide();
					$('.rightZoom').hide();
				}
				else {
					$('.flot-text').append(am.y2Axis);
					$('#'+y2.title_id).show();
					$('.rightZoom').show();
				}
			}
		});
	
	}
    
    am.update=function(updateContainer){

		var ids=['velicina','enota','faktor','ymin','ymax'];
		var container=y1;

		for (var j=0;j<2;++j){

			if (j==1) container=y2;

			for (var i=0;i<ids.length;++i){

				if (updateContainer === true)
					container[ids[i]] = $('#' + ids[i] + '-y' + (j + 1)).val();
				else
					$('#' + ids[i] + '-y' + (j + 1)).val(container[ids[i]]);
			}
		}
    }
    
    am.updateLabels = function(){

		$.each([y1,y2], function(index, y) {

			$('#' + y.title_id).html(y.velicina + '&nbsp;[' + y.enota + ']');
		});
    }
    
    am.initContainer = function(container){
	
		if (container.title_id == null) return;

		var ytitle_id = container.title_id;
		var ylabel = $('#' + ytitle_id).text();

		ylabel = ylabel.trim()

		if (ylabel == '') return;

		var y_enota = extractUnitFromLabel(ylabel);
		var y_velicina = ylabel.replace('[' + y_enota + ']','');

		y_velicina = y_velicina.trim()
		y_enota = y_enota.trim();
		
		container.velicina = y_velicina;
		container.enota = y_enota;
		
		if (am.plot !== undefined) {
			var yaxis = am.plot.getYAxes()[parseInt(container.id)];

			if (yaxis === undefined) return;

			container.ymin = yaxis.min;
			container.ymax = yaxis.max;
		}
    }
    
    $( document ).ready(function(){

    	am.init()

    });
    
}(window, document));
