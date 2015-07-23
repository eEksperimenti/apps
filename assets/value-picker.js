(function (window, document, undefined) {
        
        (function() {
              var proxied = $.plot;
              $.plot= function() {
                var args = Array.prototype.slice.call(arguments);
                if (args[2]===undefined) args[2]={};
                
                var op=args[2];
                if (op.grid===undefined) op.grid={};
                op.grid.hoverable = true;
                op.grid.clickable = true;
                
                if (op.crosshair===undefined) op.crosshair={};
                op.crosshair.mode='x';
                
                var plot=proxied.apply(this, args);//call the default is here
                vp.init(plot);
                var _setupGrid=plot.setupGrid;
                plot.setupGrid=function()
                {
                        vp.extentsChanged();
                        return _setupGrid.apply(this,arguments);
                }
                return plot;
              };
              $.plot.plugins=proxied.plugins;
        })();

    var oldvp = window.vp,
    vp = {};
    vp.version = '1.0.0';

    // define vp for Node module pattern loaders, including Browserify
    if (typeof module === 'object' && typeof module.exports === 'object') {
            module.exports = vp;
    
    // define as AMD module
    } else if (typeof define === 'function' && define.amd) {
            define(vp);
    }
    
    // define vpeaflet as a global vp variable, saving the original vp to restore later if needed
    
    vp.noConflict = function () {
            window.vp = oldvp;
            return this;
    };
    
    window.vp=vp;
    
    var markers=[];
    var hovered_point=null;
    
    this.tracks=0;
    
    this.extents=null;
    
    vp.getExtents=function()
    {
        var xmin=this.plot.getAxes().xaxis.min;
        var xmax=this.plot.getAxes().xaxis.max;
        var ymin=this.plot.getAxes().yaxis.min;
        var ymax=this.plot.getAxes().yaxis.max;
        return {xmin:xmin,xmax:xmax,ymin:ymin,ymax:ymax};
    }
    
    vp.updateMarkersAndHoveredPoint=function()
    {
        var dataset = this.plot.getData();
        for (var i=0;i<markers.length;++i) {
                var marker=markers[i];
                for (var j=0;j<marker.length;++j)
                {
                        var pos=marker[j];
                        marker[j]={x:pos.x,y:vp.interpolate(pos,dataset[j])};
                }
        }
        
        if (hovered_point!=null)
        {
                for (var i=0;i<hovered_point.length;++i) {
                        var pos=hovered_point[i];
                        hovered_point[i]={x:pos.x,y:vp.interpolate(pos,dataset[i])};
                }
                vp.updateTrackInfo(hovered_point);
        }
    }
    
    vp.extentsChanged=function()
    {
        if (this.extents==null)
        {
                this.extents=vp.getExtents();
                return false;
        }
        
        vp.updateMarkersAndHoveredPoint();
        
        var currentExtents=vp.getExtents();
        if (currentExtents.xmin==this.extents.xmin &&
            currentExtents.xmax==this.extents.xmax &&
            currentExtents.ymin==this.extents.ymin &&
            currentExtents.ymax==this.extents.ymax) {
                return false;
        }
        
        this.extents=currentExtents;
        
        vp.redraw();
        
        return true;
    }
    
    vp.redraw=function()
    {
        var ymin=this.plot.getAxes().yaxis.min;
        var ymax=this.plot.getAxes().yaxis.max;
        var ctx = this.canvas_info.getContext("2d");
        ctx.clearRect(0, 0, this.canvas_info.width, this.canvas_info.height);
        
        for (var i=0;i<markers.length;++i)
        {
                var pos=markers[i][0];
                if (pos!==undefined)
                {
                        var o1=this.plot.pointOffset({x:pos.x,y:ymin});
                        var o2=this.plot.pointOffset({x:pos.x,y:ymax});
                
                        ctx.beginPath();
                        ctx.moveTo(o2.left, o2.top);
                        ctx.lineTo(o1.left, o1.top);
                        ctx.lineWidth = 1;
                        ctx.setLineDash([5]);
                        ctx.stroke();
                }
        }
    }
    
    vp.onPlotClick= function (pos)
    {
        var ctx = this.canvas_info.getContext("2d");
        
        if (markers.length==2) {
                ctx.clearRect(0, 0, this.canvas_info.width, this.canvas_info.height);
                markers=[];
                this.onPlotHover(pos);
                return;
        }
        var ymin=this.plot.getAxes().yaxis.min;
        var ymax=this.plot.getAxes().yaxis.max;
        
	var o1=this.plot.pointOffset({x:pos.x,y:ymin});
        var o2=this.plot.pointOffset({x:pos.x,y:ymax});
        
        ctx.beginPath();
        ctx.moveTo(o2.left, o2.top);
        ctx.lineTo(o1.left, o1.top);
        ctx.lineWidth = 1;
        ctx.setLineDash([5]);
        ctx.stroke();
        
        markers.push(hovered_point);
        
        this.onPlotHover(pos);
    }
    
    vp.updateTrackInfo=function(hp)
    {
        var ahtml=[];
        for (var i = 0; i < hp.length; ++i) {
                var pos=hp[i];
                var y=pos.y;
                var csinfo='CH'+(i+1)+' ('+pos.x.toFixed(3)+','+y.toFixed(3)+');';
                
                if (markers.length==2) {
                        csinfo+=' &Delta;CH'+(i+1)+' ('+Math.abs(markers[1][i].x-markers[0][i].x).toFixed(3)+','+Math.abs(markers[1][i].y-markers[0][i].y).toFixed(3)+');';
                }
                else if (markers.length==1) {
                        csinfo+=' &Delta;CH'+(i+1)+' ('+Math.abs(pos.x-markers[0][i].x).toFixed(3)+','+Math.abs(y-markers[0][i].y).toFixed(3)+');';
                }
                
                ahtml.push(csinfo);
        }
        
        this.trac_info.html(ahtml.join(' '));
    }
    
    vp.interpolate=function(pos,series)
    {
        // Find the nearest points, x-wise
        var j;
        for (j = 0; j < series.data.length; ++j) {
                if (series.data[j]!=null && series.data[j][0] > pos.x) {
                        break;
                }
        }

        // Now Interpolate

        var y,
                p1 = series.data[j - 1],
                p2 = series.data[j];

        if (p1 == null) {
                y = p2[1];
        } else if (p2 == null) {
                y = p1[1];
        } else {
                y = p1[1] + (p2[1] - p1[1]) * (pos.x - p1[0]) / (p2[0] - p1[0]);
        }
        
        return y;
    }
    
    vp.onPlotHover=function (pos)
    {
        var axes = this.plot.getAxes();
        if (pos.x < axes.xaxis.min || pos.x > axes.xaxis.max ||
                pos.y < axes.yaxis.min || pos.y > axes.yaxis.max) {
                return;
        }

        var i, j, dataset = this.plot.getData();
        var hp=[];
        var tracks=dataset.length;
        if (this.tracks>0 && this.tracks<tracks) tracks=this.tracks;
        for (i = 0; i < tracks; ++i) {
                hp.push({x:pos.x,y:vp.interpolate(pos,dataset[i])});
        }
        
        vp.updateTrackInfo(hp);
        
        hovered_point=hp;
    }
    
    vp.init=function(plot)
    {
        this.plot=plot;
        this.placeholder=plot.getPlaceholder();
        
        var sw = plot.pointOffset({ x: plot.getAxes().xaxis.min, y: plot.getAxes().yaxis.min});
        var ne = plot.pointOffset({ x: plot.getAxes().xaxis.max, y: plot.getAxes().yaxis.max});
        
        var dy=(sw.top-ne.top);
        var font_size=0.025*dy;
        
        this.placeholder.append("<canvas id='canvas-info' width='"+(ne.left-sw.left)+"' height='"+(sw.top-ne.top)+"'></canvas>");
        this.canvas_info=$('#canvas-info')[0];
        this.placeholder.append("<div id='trac-info' style='background:rgba(255,255,255,0.7);font: "+font_size+"px arial, sans-serif;position:absolute;left:" + (sw.left + 4) + "px;top:" + (sw.top-1.2*font_size) + "px;color:#666;'></div>");
        this.trac_info=$('#trac-info');
        
        this.placeholder.bind("plothover",  function (event, pos, item) {vp.onPlotHover(pos);});
        this.placeholder.bind("plotclick",  function (event, pos, item) {vp.onPlotClick(pos);});
    };
    
}(window, document));
