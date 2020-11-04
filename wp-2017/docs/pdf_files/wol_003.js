if(!$("html").hasClass("js_en")){$("html").addClass("js_en")
}var proxied=((location.hostname.indexOf("onlinelibrary.wiley.com")!=-1)&&(location.hostname.substring(location.hostname.indexOf("onlinelibrary.wiley.com")+23)==""))?false:true;
$(function(){$.ol={};
$(".publicationTypes #allTypes,.subjectsAndAccess #allTopics, #allAsist").searchSelectAll();
$(document).globalMessaging();
if($("#accordion").length>0){$("#accordion").accordion({header:"h2"})
}$(".contextTrigger").contextFilter();
$("#additionalInformation").slider();
$("#login #loggedIn .profile>li").profileMenu();
$("#issueTocGroups, #titles, #publications, .articles, .books").selectAll();
$(".emrw-table").mrwTables();
$(".jumpList").jumpList();
$("#loginEmail, #loginPassword").loginLabels();
if($("#pdf").length){$(window).resize(function(){$("#pdf").children("iframe").height(($(window).height()-$("#pdfHeader").height())-2)
});
$(window).triggerHandler("resize")
}if(!$("#mailUpdates").attr("checked")){$("#mailUpdates").parents("fieldset").next().slideUp()
}$("#mailUpdates").click(function(){if($(this).attr("checked")){$(this).parents("fieldset").next().slideDown()
}else{$(this).parents("fieldset").next().slideUp()
}});
!proxied&&$(".issuesInYear").issueTree();
$("#browseBySubject").subjectTree();
$("#globalMenu ul li:nth-child(3)").addResourceMenu();
$.ol.cleanAJAXResponse=function(g){if(g.indexOf("<body>")>-1){return/<body[^>]*>([\S\s]*?)<\/body>/.exec(g,"ig")[1]
}else{return g
}};
if(!$("#mailPromotionRequested").attr("checked")){$("#mailPromotionRequested").parents("fieldset").next().hide()
}$("#mailPromotionRequested").click(function(){if($(this).attr("checked")){$(this).parents("fieldset").next("fieldset").slideDown()
}else{$(this).parents("fieldset").next("fieldset").slideUp()
}return true
});
$.ol.textSlider=function(g,h){$(g).each(function(){var j=$(this),i=j.height();
if(i>=200){j.css({height:"20em",overflow:"hidden",position:"relative",marginBottom:"0.5em"});
$("<a/>",{text:h[0]}).toggle(function(){$(this).text(h[1]);
j.height(i);
return false
},function(){$(this).text(h[0]);
j.height("20em");
return false
}).insertAfter(j).wrap('<p id="showContent">')
}})
};
$.ol.textSlider("#bookHome #homepageContent",["More about this book summary","Less about this book summary"]);
$.ol.textSlider("#bookHomeSeries #homepageContent",["More about this book series","Less about this book series"]);
if($("#mrwHome").length>0){$.ol.textSlider("#mrwHome #homepageContent:has(~ #rightColumn, ~ #leftColumn)",["More about this book","Less about this book"])
}($.ol.keyStrokeCollector=function(){$(document).keydown(function(h){var g={ctrl:(h.ctrlKey)?true:false,shift:(h.shiftKey)?true:false,alt:(h.altKey)?true:false,key:h.keyCode};
$(this).data("keyDown",g)
});
$(document).keyup(function(g){$(this).removeData("keyDown")
})
})();
$.ol.Tree=function(i,g){this.branches=[];
this.selector=g||i;
var h=this.params={};
$.each($.extend({},$.ol.Tree.defaults,(arguments.length==1)?{}:i),function(k,j){h[k]=j
});
this.init()
};
$.extend($.ol.Tree.prototype,{init:function(){var g=this;
if(!this.params.ajax){$(this.selector).find("li > span").each(function(){var k=$(this).removeAttr("class").wrap('<a href="#"></a>').parents("a").addClass("branchLabel").addClass("open");
g.branches.push(new $.ol.Tree.Branch(k))
});
this.collapseAll()
}else{$(this.selector).find("li > a.branchLabel").each(function(){$(this).click(function(){var l=this,k=$(this).next("ol");
if(k&&k.css("display")=="block"){k.slideUp(function(){$(l).removeClass("open").addClass("closed")
})
}else{if(k&&k.css("display")=="none"){k.slideDown(function(){$(l).removeClass("closed").addClass("open")
})
}else{$.ajax({type:"GET",url:$(l).attr("href"),dataType:"html",dataFilter:function(n,m){return $.ol.cleanAJAXResponse(n)
},beforeSend:function(){$(l).removeClass("closed").addClass("fetching")
},success:function(m){$(l).after($(m).css("display","none"));
$(l).next("ol").slideDown(function(){$(l).removeClass("fetching").addClass("open")
});
$(l).next("ol").mrwTree({ajax:true})
},error:function(m,n,o){$(l).removeClass("fetching").addClass("closed")
}})
}}return false
})
})
}if($(this.selector).find("li > span:first").length){if(this.params.expandAll||this.params.collapseAll){var i=$('<ul class="productMenu"></ul>').prependTo($(this.selector).parent())
}if(this.params.expandAll){var j=$("<li/>").appendTo(i);
$('<a href="#">Expand All</a>').appendTo(j).click(function(){return g.expandAll()
})
}if(this.params.collapseAll){var h=$("<li/>").appendTo(i);
$('<a href="#" id="collapseAll">Collapse All</a>').appendTo(h).click(function(){return g.collapseAll()
})
}}},expandAll:function(){$.each(this.branches,function(){this.expandStep.apply(this.selector,[])
});
return false
},collapseAll:function(){if(this.branches.length!=0){$.each(this.branches,function(){this.collapse.apply(this.selector,[])
})
}else{$(this.selector).find("li > a.open").removeClass("open").addClass("closed").next("ol").slideUp()
}return false
}});
$.ol.Tree.defaults={expandAll:false,collapseAll:false,ajax:false};
$.ol.Tree.Branch=function(g){this.selector=g;
this.init()
};
$.extend($.ol.Tree.Branch.prototype,{init:function(){var g=this;
$(this.selector).click(function(){if($(this).hasClass("closed")){g.expand.apply(this,[])
}else{g.collapse.apply(this,[])
}return false
})
},expand:function(g){$.ol.Tree.Branch.prototype.expandStep.apply(this,[]);
if(g){$(this).parent().find("a:has(span)").each(function(){$.ol.Tree.Branch.prototype.expandStep.apply(this,[])
})
}},expandStep:function(){$(this).removeClass("closed").addClass("open").next("ol").slideDown()
},collapse:function(g){$(this).removeClass("open").addClass("closed").next("ol").slideUp()
}});
$.fn.mrwTree=function(g){return this.each(function(){new $.ol.Tree(g,this)
})
};
!proxied&&$("#mrwBrowseByTopic #browseMrw").mrwTree({ajax:true,collapseAll:true});
$("#mrwBrowseByTOC #browseMrw").mrwTree({expandAll:true,collapseAll:true});
$(".decisionTree").dynamicSelectGroup();
if($("#searchByCitation").length){$("#scope").append('<option value="byCitation">By Citation</option>');
$("#scope").change(function(){if($(this).find("option:selected").text()=="By Citation"){$("#searchByCitation").slideDown(function(){$("#searchText, #searchSiteSubmit").attr("disabled","disabled")
})
}else{$("#searchByCitation").slideUp(function(){$("#searchText, #searchSiteSubmit").removeAttr("disabled")
})
}});
$("#searchByCitation p.error").length&&$("#scope").val("byCitation").triggerHandler("change")
}$("#resourcesMenu").parents("li").hover(function(){$("#resourcesMenu").toggle()
});
$("#resourcesMenu ul").bgiframe({top:20});
$("#issueToc .figZoom img").load(function(){$(this).css("visibility","visible");
if($(this).height()>300){$(this).height(300)
}if($(this).width()>300){$(this).css("float","none")
}}).each(function(){if(this.complete||(jQuery.browser.msie&&parseInt(jQuery.browser.version)==6)){$(this).triggerHandler("load")
}});
$("#fulltext .firstPageContainer img").load(function(){$(this).removeAttr("height").removeAttr("width");
if($(this).width()>752){$(this).width(752)
}}).each(function(){if(this.complete||(jQuery.browser.msie&&parseInt(jQuery.browser.version)==6)){$(this).triggerHandler("load")
}});
$("#fulltext a.movingMolecule").each(function(){$(this).click(function(){window.open($(this).attr("href"),$(this).index(),"width=1024,height=790,scrollbars=yes");
return false
})
});
if($("meta[name='citation_journal_title']").length||($("#pdf").length&&$("#productTitle").length)){var e=($("#pdf").length)?$("#productTitle").attr("href").split("(ISSN)")[1]:$("meta[name='citation_issn']").attr("content");
var a=($("#pdf").length)?window.location.href.split("/doi/")[1].split("/pdf")[0]:$("meta[name='citation_doi']").attr("content");
$.getJSON("http://www.deepdyve.com/rental-link?docId="+a+"&fieldName=journal_doi&journal="+e+"&affiliateId=wiley&format=jsonp&callback=?",function(h){if(h.status==="ok"){var j=$('<p><a class="rentalLink">Rent this article at DeepDyve</a></p>');
var i=$('<div id="deepDyve" class="topLeftRoundCornerNew"><h2>Rent this article through DeepDyve</h2><p>View a read-only copy of this article through our partner DeepDyve, the largest online rental service for scientific and scholarly content. DeepDyve will safeguard user privacy and your information will not be sold to a third party.</p><p>Read more about our pilot program making a portfolio of Biotechnology journals available through DeepDyve.</p><p><a href="http://eu.wiley.com/WileyCDA/PressRelease/pressReleaseId-84017.html">Press Release</a></p></div>');
j.find("a").attr("href",h.url);
i.insertAfter("#accessDenied .access .login");
j.clone(true).insertAfter("#deepDyve p:first");
var g=$('<li><span style="color: red; padding-right: 0.4em; font-weight: bold;">NEW!</span> </li>');
j.find("a").clone(true).appendTo(g);
g.appendTo("#accessDeniedOptions")
}})
}$("#downloadStatisticalData form").live("submit",function(){var g=$(this).find("#tAndCs"),h=$(this).find("label[for='tAndCs']");
if(!g.is(":checked")){if($(this).find(".error").length==0){$('<label class="error" for="tAndCs">Please agree to the terms and conditions.</label>').insertAfter(h)
}return false
}});
window.addthis_config={services_compact:"digg,diigo,citeulike,googlereader,www.mendeley.com,stumbleupon,facebook,twitter,delicious,connotea",services_custom:{name:"mendeley",url:"http://www.mendeley.com?url={{url}}&title={{title}}",icon:"http://www.mendeley.com/favicon.ico"}};
addthis.addEventListener("addthis.menu.share",function(){$("#at15s,#at16lb").css({display:"none",zIndex:"1"})
});
$("#promosAndTools .titleTools").socialBookmarks();
var d=window.institutions||[];
$("#institutionalAndAthensLogin #institutionName").autocomplete({source:d,minLength:2});
$("#exportCitation #citationFormat").live("change",function(){var g=$(this).parents("form");
if($(this).val()==="REFWORKS"){g.attr("target","_blank");
$('<p class="fieldAssistance">This option will open up a new window.</p>').insertAfter(this)
}else{g.removeAttr("target").find(".fieldAssistance").remove()
}});
if($("frame[name='body']").length&&$("frame[name='initwin']").length){if(top.location.search){var c=top.location.search,b=c.substring(c.lastIndexOf("=")+1),f=c.substring(c.indexOf("=")+1,c.indexOf("&"));
if(f){top.frames.body.location.href=f+"#"+b
}}}});
function RightslinkPopUp(a){window.open(a,"Rightslink","location=no,toolbar=no,directories=no,status=no,menubar=no,scrollbars=yes,resizable=yes,width=650,height=550")
};