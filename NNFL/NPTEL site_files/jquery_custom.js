$(function(){

    /************Accordian Inner Tabs Functions***************/
	$("h2.trigger").click(function(){
		$(this).toggleClass("inactive").next().slideToggle("fast");
	});
	//  var is_chrome = navigator.userAgent.toLowerCase().indexOf('chrome') > -1;
	//		  if(!is_chrome){
  /************End---Accordian Inner Tabs Functions***************/
      $(document).ready(function() {
  
		  /************Close Accordian***************/
          $('#sideClose').click(function() {
			  $("#sideClose").hide();
              $(this).parent().animate({width:'toggle'});
			   setTimeout(function(){
              $("#tabs").css("width",'130%');
								   },500);
            
                 $("#tabs").css("margin-left",00);
			
              setTimeout(function(){
				   $("#open").show(); 
                                  $("#open").animate({width:'18px'});
								   },450);
                                
          });
		  /************End---Close Accordian***************/
		  /************Open Accordian***************/
          $('#open').click(function() {
              
               
               $("#tabs").css('width', '100%');
               setTimeout(function(){
			                  $("#sideMenuId").animate({width: 'toggle'});
								   },100);
			   setTimeout(function(){
								   $("#sideClose").show();
								   $("#open").hide();
								   },500);
			    
          });
		  /************End---Open Accordian***************/
      });
      onload=function(){
      if (document.getElementsByClassName == undefined) {
    	document.getElementsByClassName = function(className)
     	{
		var hasClassName = new RegExp("(?:^|\\s)" + className + "(?:$|\\s)");
		var allElements = document.getElementsByTagName("*");
		var results = [];

		var element;
		for (var i = 0; (element = allElements[i]) != null; i++) {
			var elementClass = element.className;
			if (elementClass && elementClass.indexOf(className) != -1 && hasClassName.test(elementClass))
				results.push(element);
		}

		return results;
	}
}
}
//}
});

function checkReason(){
	try{
	if(document.getElementById("reason").value!=''){
		saveRating();
	}else{
		document.getElementById("div_reason").innerHTML= "<font color=\"red\" size=1>Please Enter the Reason for poor Rating</font>";
		document.getElementById("div_reason").style.border = "0px";
		return false;
	}
	}catch(e){}
}
function signIn(){
	$(".signIn").html("<font color=red>Please Sign in.</font>");
}
function askAquestion(courseId,lectureId){
    //alert("courseId "+courseId+" lectureId "+lectureId);	
	var url = "../askaquestion.php";
	var qstr = "courseId="+courseId+"&lectureId="+lectureId;
	//alert(url+"?"+qstr);
	try{
		responseText = getResponse(url,qstr,"POST");
	}catch(e){alert(e.message)}
	$(".css-panes>div").html(responseText);
}
function faq(courseId,lectureId){
    //alert("courseId "+courseId+" lectureId "+lectureId);	
	var url = "../faq.php";
	var qstr = "courseId="+courseId+"&lectureId="+lectureId;
	//alert(url+"?"+qstr);
	try{
		responseText = getResponse(url,qstr,"POST");
	}catch(e){alert(e.message)}
	$(".css-panes>div").html(responseText);
}
function saveRating(){
       try{
		   document.getElementById("poorRatingReason").style.display = "none";
           document.getElementById("div_reason").innerHTML = "";
	   }catch(e){}
	   var ratingVal=0;
	   var lectureid=0;
	   var subjectid=0;
	   var userID=0;
	   var reason = "";
	   var starArray = new Array("onestar","twostar","threestar","fourstar","fivestar");
       try {
           eval("ratingVal=document.getElementById(\"currentRating\").value");
       } catch(e) {}
       try {
           eval("lectureid=document.getElementById(\"lectureid\").value");
       } catch(e) {}
       try {
           eval("subjectid=document.getElementById(\"subjectid\").value");
       } catch(e) {}
       try {
           eval("reason=document.getElementById(\"reason\").value");
       } catch(e) {}
       try {
           eval("userID=document.getElementById(\"userID\").value");
       } catch(e) {}
	   if(subjectid>0 && lectureid>0){
		   var url = "saveRating.php";
		   var overAllRating = 0;
		   var timesRated = 0;
		   var alreadyRated = "";
		   var qstr = "rating="+ratingVal+"&lectureid="+lectureid+"&subjectid="+subjectid+"&reason="+reason+"&userID="+userID;
           try {
              xmlDoc = getXMLDoc(url,qstr,"POST");
           } catch(e){}
           try {
               document.getElementById("reason").value='';
			   try{
                   var rating = xmlDoc.getElementsByTagName("rating") ;
                   for ( var i = 0; i < rating.length ; i++ ) {
			           overAllRating = rating[i].getElementsByTagName("overAllRating")[0].firstChild.nodeValue;
			           timesRated = rating[i].getElementsByTagName("timesRated")[0].firstChild.nodeValue;
			           alreadyRated = rating[i].getElementsByTagName("alreadyRated")[0].firstChild.nodeValue;
                   }
				   if(timesRated>0){
			           document.getElementById("timesRated").innerHTML = timesRated;
				   }
			   }catch(e){}
			   if(alreadyRated=="YES"){
   			       $(".signIn").html("<font color=red>You have already rated this lecture</font>");
   			       document.getElementById("alreadyRatedVal").value = 1;
			   }else if (alreadyRated=="NO"){
				   if( timesRated > 0){
			           currentRating = Math.round(overAllRating/timesRated);
				   }else{
			           currentRating =0;
				   }
				   
			       ratingClass="";
			       for(sc=0;sc<starArray.length;sc++){
    				   if(currentRating==(sc+1)){
	                   ratingClass=starArray[sc];
				       }
			       }
			       $("#rating").removeClass();
			       $("#rating").addClass("rating "+ratingClass);
			   }
           } catch(e) {}
	   }
}

function rating(val){
	document.getElementById("currentRating").value=val;
	checkAlreadyRated();
	var alreadyRatedVal = $("#alreadyRatedVal").attr("value");
	if(alreadyRatedVal==0){
    	if(val<3){
 	    	document.getElementById("ratingReasonStar").innerHTML = "Reason for "+val+" star rating";
 	    	document.getElementById("poorRatingReason").style.display = "block";
    	}else{
	    	saveRating();
    	}
	}
}
function checkAlreadyRated(){
       try {
           eval("ratingVal=document.getElementById(\"currentRating\").value");
       } catch(e) {}
       try {
           eval("lectureid=document.getElementById(\"lectureid\").value");
       } catch(e) {}
       try {
           eval("subjectid=document.getElementById(\"subjectid\").value");
       } catch(e) {}
       try {
           eval("reason=document.getElementById(\"reason\").value");
       } catch(e) {}
       try {
           eval("userID=document.getElementById(\"userID\").value");
       } catch(e) {}
	   if(subjectid>0 && lectureid>0){
		   var url = "saveRating.php";
		   var overAllRating = 0;
		   var timesRated = 0;
		   var alreadyRated = "";
		   var qstr = "rating="+ratingVal+"&lectureid="+lectureid+"&subjectid="+subjectid+"&reason="+reason+"&userID="+userID+"&chk=YES";
           try {
              xmlDoc = getXMLDoc(url,qstr,"POST");
           } catch(e){}
           try {
               document.getElementById("reason").value='';
			   try{
                   var rating = xmlDoc.getElementsByTagName("rating") ;
                   for ( var i = 0; i < rating.length ; i++ ) {
			           overAllRating = rating[i].getElementsByTagName("overAllRating")[0].firstChild.nodeValue;
			           timesRated = rating[i].getElementsByTagName("timesRated")[0].firstChild.nodeValue;
			           alreadyRated = rating[i].getElementsByTagName("alreadyRated")[0].firstChild.nodeValue;
                   }
				   if(timesRated>0){
			           document.getElementById("timesRated").innerHTML = timesRated;
				   }
			   }catch(e){}
          }catch(e){}
	   }
	if(alreadyRated=="YES"){
   	    $(".signIn").html("<font color=red>You have already rated this lecture</font>");
   	    document.getElementById("alreadyRatedVal").value = 1;
	}
	return;
}

function getXMLDoc(url,queryString,postMethod) {
    var xmlDoc;
    var moz = (typeof document.implementation != 'undefined') && (typeof document.implementation.createDocument != 'undefined');
    if (moz) {

        try {
            var parser = new DOMParser(); 
            xmlDoc = parser.parseFromString(getResponse(url,queryString,postMethod),"text/xml"); 
            xmlDoc.async=false;
        } catch(e) {
	    alert('Error : '+e);
        }
    }  else {
        try {
            xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
            xmlDoc.async=false;
            xmlDoc.loadXML(getResponse(url,queryString,postMethod));
        }  catch(e) {
      	    alert('Error : '+e);
	}        
    }
        return xmlDoc;
}  
function getResponse(url,queryString, postMethod) {
    try{
        try {
            xmlHttp = new XMLHttpRequest()
        } catch (e) { 
            try {
                xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
            } catch (e) {  
               xmlHttp = false; 
            }
        }
        if (!xmlHttp) return null;
            //xmlHttp.overrideMimeType("text/xml");
            xmlHttp.open(postMethod, url, false);
            xmlHttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            xmlHttp.send(queryString);
            return (xmlHttp.responseText+"");
        } catch (e) {
            return e.message; 
        }
    }



