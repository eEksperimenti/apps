(function (window, document, undefined) {
	(function() {
	      var proxied = $.plot;
	      $.plot= function() {
		var args = Array.prototype.slice.call(arguments);
		
		if(am.yaxis2==true)
		{
			if (y2.element==null)
			{
				var y2element=$('<div id="'+y2.title_id+'" class="y2title" style="display: block;"></div>');
				args[0].parent().append(y2element);
				y2.element=y2element;
			}
			
			if (args[2]===undefined) args[2]={};
			
			var options=args[2];
			if (options.yaxes===undefined) options.yaxes=[{},{}];
			options.yaxes[1].position='right';
			options.yaxes[1].alignTicksWithAxis=y2.alignTicksWithAxis.prop("checked")?1:0;
			
			am.initContainer(y2);
			am.update();
			am.updateLabels();
		}

		am.plot=proxied.apply(this, args);//call the default is here
		$('#y2title,.y2title').css('left',(am.plot.getPlaceholder().parent().width()+10)+'px')
		
		var _setupGrid=am.plot.setupGrid;
    am.plot.setupGrid=function()
    {
			var data=am.plot.getData();
			if (am.yaxis1==false) data[0].lines.show=false;
			if (am.yaxis2==false) data.pop();
			if (data[1]!==undefined) data[1].yaxis=2
				
			//////////////////////////
			var len=data[0].data.length;
			var m1=eval(y1.faktor);
			var m2=eval(y2.faktor);
			for (var i=0;i<len;++i) {
				var va=data[0].data[i][1];
				var vb=0.0;
				if (data[1]!==undefined) vb=data[1].data[i][1];
				data[0].data[i][1]=m1[0]*va+m1[1]*vb+m1[2];
				if (data[1]!==undefined) data[1].data[i][1]=m2[0]*va+m2[1]*vb+m2[2];
			}
				
			var options=am.plot.getOptions();
			if (y1.rangeChanged)
			{
				options.yaxes[0].min = y1.ymin;
				options.yaxes[0].max = y1.ymax;
				y1.rangeChanged=false;
			}
			else {
				y1.ymin=options.yaxes[0].min;
				y1.ymax=options.yaxes[0].max;
			}
			
			if (data[1]!==undefined)
			{
				if (y2.rangeChanged)
				{
					options.yaxes[1].min = y2.ymin;
					options.yaxes[1].max = y2.ymax;
					y2.rangeChanged=false;
				}
				else {
					y2.ymin=options.yaxes[1].min;
					y2.ymax=options.yaxes[1].max;
				}
				options.yaxes[1].alignTicksWithAxis=y2.alignTicksWithAxis.prop("checked")?1:0;
			}
				
				/////////////////////////////////////
			am.plot.setData(data);
      return _setupGrid.apply(this,arguments);
    }
		return am.plot;
	      };
	      $.plot.plugins=proxied.plugins;
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
    
    window.am=am;
    
    am.div_id='nastavitve';
    am.yaxis1=true;
		am.yaxis2=true;
    var y={'id':'',title_id:'','velicina':'','enota':'','faktor':'[1, 0, 0]', 'ymin':-1,'ymax':1,'rangeChanged':false}
    var y1=$.extend(true, {}, y);
    var y2=$.extend(true, {}, y);
    y2.faktor='[0,1,0]';
    y1.id='y1';
    y2.id='y2';
    y1.title_id='ytitle';
    y2.title_id='y2title';
    
    function extractUnitFromLabel(label)
    {
	return label.substring(label.lastIndexOf("[")+1,label.lastIndexOf("]"));
    }
    
    addElement=function(y)
    {
	if (y.title_id==null) return;
	
	var element=$('#'+y.title_id);
	
	if (element.length==0) {
		element=$('.'+y.title_id).first();
		if (element.length==0) element=null; 
	}
	y.element=element;
    }
    
    am.init=function()
    {
	if (am.yaxis2==false) y2.title_id=null;
	
	var html="<form role='form' class='nastavitve'>\
			<div class='form-group '>\
			  <label for='velicina-y%1'>Veličina</label>\
			  <input type='text' class='form-control' id='velicina-y%1'>\
			</div>\
			<div class='form-group'>\
			  <label for='enota-y%1'>Enota</label>\
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
	
	$('#'+am.div_id).html('<div class="checkbox"><label><input type="checkbox" class="axis-toggler" id="left-axis" value="" checked><b>Leva Y os (ordinata)</b></label></div>'+html.replace(/%1/g, '1')+
	'<hr><div class="checkbox"><label><input type="checkbox" class="axis-toggler" id="right-axis" value="" checked><b>Desna Y os (ordinata)</b></label></div>'+html.replace(/%1/g, '2')+cb);
	$('#y2title,.y2title').css('right','0');
	$('.nastavitve > .form-group > .form-control').keypress(function(event){
		if (event.which==13)
		{
			am.update(true);
			am.updateLabels();
		}
	});
	
	$.each([y1,y2], function(index, value) {addElement(value)});
	$.each([y1,y2], function(index, value) {am.initContainer(value)});
	y2.velicina=y1.velicina;
	y2.enota=y1.enota;
	y2.alignTicksWithAxis=$('#alignTicksWithAxis');
	am.update();
  $('.axis-toggler').click(function(){
		var cb=$(this);
		if (cb.attr('id')=='left-axis')
		{ 
			am.yaxis1=cb.prop("checked");
			if (!am.yaxis1)
			{
				$('#'+y1.title_id).hide();
			}
			else {
				$('#'+y1.title_id).show();
			}
		}
		else if (cb.attr('id')=='right-axis')
		{
			am.yaxis2=cb.prop("checked");
			if (!am.yaxis2)
			{
				am.y2Axis=$('.y2Axis');
				am.y2Axis.remove();
				$('#'+y2.title_id).hide();
			}
			else {
				$('.flot-text').append(am.y2Axis);
				$('#'+y2.title_id).show();
			}
		}
	});
	}
    
    am.update=function(updateContainer)
    {
	var ids=['velicina','enota','faktor','ymin','ymax'];
	
	var container=y1;
	for (var j=0;j<2;++j)
	{
		if (j==1) container=y2;
		for (var i=0;i<ids.length;++i)
		{
			if (updateContainer===true)
			{
				container[ids[i]]=$('#'+ids[i]+'-y'+(j+1)).val();
				container[ids[i]].rangeChanged=true;
			}
			else
				$('#'+ids[i]+'-y'+(j+1)).val(container[ids[i]]);
		}
	}
    }
    
    am.updateLabels=function()
    {
	$.each([y1,y2], function(index, y) {
		$('#'+y.title_id).html(y.velicina+'&nbsp;['+y.enota+']');
	});
    }
    
    am.initContainer=function(container)
    {
	if (container.title_id==null) return;
	var ytitle_id=container.title_id;
	var ylabel=$('#'+ytitle_id).text();
	ylabel=ylabel.trim()
	if (ylabel=='') return;
	var y_enota=extractUnitFromLabel(ylabel);
	var y_velicina=ylabel.replace('['+y_enota+']','');
	y_velicina=y_velicina.trim()
	y_enota=y_enota.trim();
	
	container.velicina=y_velicina;
	container.enota=y_enota;
	
	if (am.plot!==undefined) {
		var yaxis=am.plot.getYAxes()[parseInt(container.id)];
		if (yaxis===undefined) return;
		container.ymin=yaxis.min;
		container.ymax=yaxis.max;
	}
    }
    
    $( document ).ready(function(){am.init()});
    
}(window, document));
