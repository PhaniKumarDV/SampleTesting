$('.nav li').click(function()
{                                  
localStorage.setItem("selectedMenu", $(this).attr("data-target"));

$(this).siblings().find("ul").removeClass("in");  
$(this).siblings().addClass("collapsed");          
});                                                

var menu = localStorage.getItem("selectedMenu");
$("[data-target='"+menu+"']").removeClass("collapsed");                                                                     
var url = window.location.pathname;                                  
var searchedUrl = url.split('=')[1].split('/');                      
var searchText = searchedUrl[2]+'/'+searchedUrl[3]; 
$(document).ready( function() {                 
$('.nav ul li a').each(function(){                                   
   var myHref= $(this).attr('href');                                 
   if( url == myHref) {                            
        $(this).closest("li").addClass("active");                    
        $(this).closest("ul").addClass('in');                          
        $(this).closest('ul').closest('li').removeClass('collapsed');
   }else if(myHref.indexOf(searchText) !== -1){                      
        $(this).closest("li").addClass("active");                    
        $(this).closest("ul").addClass('in');                          
        $(this).closest('ul').closest('li').removeClass('collapsed');
   }                                                                 
});
});
