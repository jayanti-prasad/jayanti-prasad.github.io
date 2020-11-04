$(function(){$("#fulltext .graphicalAbstract .figZoom").click(function(){$.fancybox.staticUseSetup();
$.fancybox.showActivity();
var d=$(this);
var c=$(this).attr("href");
var b=new Image();
$(b).load(function(){$.fancybox.hideActivity();
var e=$("<div />");
$(b).css("margin","10px").appendTo(e);
d.parent().find(".caption").css({"padding-top":"10px","padding-left":"10px","padding-right":"10px"}).appendTo(e);
$.fancybox({padding:0,margin:0,content:e,titleShow:false,autoScale:false,onComplete:function(){}})
}).attr("src",c);
return false
});
$("#fulltext .section .figZoom").click(function(){$.fancybox.staticUseSetup();
$.fancybox.showActivity();
var f=$(this),d=$(this).attr("href"),c=new Image(),e=$(this).parents(".figure").find(".caption .downloadToPowerpoint a").attr("href"),b=$("<div />");
$(c).load(function(){$.fancybox.hideActivity();
$(c).css("margin","10px").appendTo(b);
var h=f.parent().find(".caption").clone();
h.find(".downloadToPowerpoint").remove();
h.find("a").click(function(){$.fancybox.close()
});
h.css({"padding-top":"10px","padding-left":"10px","padding-right":"10px"}).appendTo(b);
b.width($(c).attr("width")+20);
if(e){var g=$("<div id='figureNavigation'><a class='powerPoint' href='"+e+"'>Download figure to PowerPoint</a></div>");
g.appendTo(b)
}$.fancybox({padding:0,margin:0,content:b,titleShow:false,autoScale:false,onComplete:function(){}})
}).attr("src",d);
return false
});
if($("#totalViews span").text()!=0){$('<a href="metrics">view chart</a>').appendTo("#totalViews")
}$(".tabbedContent a[href=metrics]").parents("li").hide();
$("#totalViews a").click(function(){$.fancybox.staticUseSetup();
$.fancybox.showActivity();
var d=window.location.pathname.split("/"),b=d.slice(0,-1).join("/");
$.ajax({type:"GET",url:b+"/metricsData",dataType:"html",dataFilter:function(f,e){return $.ol.cleanAJAXResponse(f)
},success:function(g,e){$.fancybox.hideActivity();
var f=$("<div>").append($(g).find("#usageDateRange")).append($(g).find("#usageTotals")).append('<div class="tabbedContent"><ul><li id="cumulativeGraph" class="active"><span>Cumulative Usage</span></li></ul></div>').append($('<div class="dataTable">').append($(g).find(".dataTable table").clone())).append($(g).find(".tableComments")).append($(g).find("#aboutUsageData"));
$.fancybox({content:f.html(),width:752,height:520,autoDimensions:false,autoScale:false,scrolling:"no"});
c();
$("#fancybox-inner .flot-graph").eq(1).hide()
}});
function c(){var f={series:"columns",width:"96%",height:"220px",position:"replace",xaxisTransform:function(g){return(new Date(g.split(" ")[0]+" 1, "+g.split(" ")[1])).getTime()
}},e={legend:{position:"nw"},xaxis:{mode:"time",timeformat:"%b %y",minTickSize:[1,"month"],show:false},grid:{hoverable:true,clickable:true,backgroundColor:"#fff",color:"#000",borderWidth:0},colors:["#b695ff","#007E8B"]};
$("#fancybox-wrap table").eq(0).graphTable(f,$.extend(e,{yaxis:{min:0,tickDecimals:0},series:{lines:{lineWidth:3,show:true},points:{show:true}}}))
}return false
});
$("#fancybox-inner .tabbedContent li").live("click",function(){var b=$(this);
$("#fancybox-inner .flot-graph").hide();
$(this).parent("ul").children().removeClass("active");
if(b.index()===0){$(".flot-graph").eq(0).show();
b.addClass("active")
}else{if(b.index()===1){$(".flot-graph").eq(1).show();
b.addClass("active")
}}return false
});
function a(b,d,c){$('<div id="tooltip">'+c+"</div>").css({position:"absolute",display:"none",top:d-30,left:b+6,padding:"3px","background-color":"#5d5d5d",color:"#fff","font-weight":"bold",zIndex:1000000,"font-size":"1.3em"}).appendTo("body").show()
}$(".flot-graph").live("plothover",function(c,j,n){var f=null;
if(n){if(f!=n.dataIndex){f=n.dataIndex;
$("#tooltip").remove();
var l=n.datapoint[0],k=n.datapoint[1],b=n.series.data[n.dataIndex][1],e=b.replace(/(\d)(?=(\d\d\d)+(?!\d))/g,"$1,"),h=["January","February","March","April","May","June","July","August","September","October","November","December"],d=new Date(l),i=n.series.label.toUpperCase(),g=$("#fancybox-inner #usageDateRange").text(),m=$(this).index()===1?" views in ":" views "+g.slice(g.lastIndexOf("from")+5,g.lastIndexOf("-"))+" - ";
a(n.pageX,n.pageY,e+" "+i+m+h[d.getMonth()]+" "+d.getFullYear())
}}else{$("#tooltip").remove();
f=null
}}).live("mouseleave",function(){$("#tooltip").remove()
});
$("#mrwFulltext .fig-thumbnail-href").click(function(){$.fancybox.staticUseSetup();
$.fancybox.showActivity();
var d=$(this);
var c=$(this).attr("href");
var b=new Image();
$(b).load(function(){$.fancybox.hideActivity();
var h=$("<div />").css("padding","10px");
var f=$("<div />");
$(b).appendTo(f);
if(d.parent("td").length){var e=$("<p />").css({"padding-top":"10px","margin-bottom":"0"});
var g=(d.parent().nextAll("td").length==1)?d.parent().next().html():d.text();
e.html(g).appendTo(f)
}h.width($(b).attr("width")+20);
f.appendTo(h);
$.fancybox({padding:0,margin:0,content:h,titleShow:false,autoScale:false,onComplete:function(){h.width((h.parent().height()<h.parent().attr("scrollHeight"))?h.width()-20:h.width())
}})
}).attr("src",c);
return false
});
$(".articleAbstract > .figZoom").fancybox({titleShow:false,cyclic:false,autoScale:false});
$(".imageTable img").css("display","block").each(function(){var b=$(this);
b.wrap("<a href='#' />").click(function(){$(this).fancybox({titleShow:false,cyclic:false,autoScale:false,content:b.clone()});
return false
})
});
$(".referenceLink").click(function(){$.fancybox.staticUseSetup();
var d=$("<ul id='overlayList' />");
var c=$(this).attr("rel");
var b=10;
$.each(c.split("#"),function(e,i){if(i.indexOf("#")==-1&&e!=0){var g=$("#"+i).clone();
var h=g.find("cite");
var f=$("<a />");
f.attr("href","#"+i);
f.click(function(){$.fancybox.close()
});
h.wrap(f);
b+=$("#"+i).height();
g.appendTo(d)
}});
$.fancybox({content:d,width:752,height:b,autoDimensions:false,autoScale:false});
return false
});
$("#viewPrivacyPolicy, #viewTermsAndConditions").fancybox({titleShow:false,width:800,autoDimensions:false,autoScale:false,cyclic:false});
$(".payPerViewForm .fieldAssistance > a").fancybox({titleShow:false,width:480,height:410,autoDimensions:false,autoScale:false,cyclic:false});
!proxied&&$("li.email > a").fancybox({titleShow:false,width:620,height:410,autoDimensions:false,autoScale:false,cyclic:false});
!proxied&&$("li.citation > a, a[href='downloadstats']").fancybox({titleShow:false,width:480,height:200,autoDimensions:false,autoScale:false,cyclic:false})
});