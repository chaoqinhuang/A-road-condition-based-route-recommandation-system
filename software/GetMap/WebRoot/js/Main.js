/**
 * Created by 昕点陈 on 2017/11/4.
 */
var data;
var hitLine;

window.onload = function () {
    data = document.getElementsByName("data");
};

function addWeight(){
	var node1 = parseInt(document.getElementsByName("node1").innerHTML);
	var node2 = parseInt(document.getElementsByName("node2").innerHTML);
    document.getElementById("bestRoute").innerHTML = "The best route is 3 -> 2 -> 4 -> 6"; 
	if(node1 > node2){
    	temp = node2;
    	node2 = node1;
    	node1 = temp;
    }
	
	$.ajax({  
        type: "POST",   
        contentType:"application/json;charset=UTF-8",
        url:"../WebRoot/set.json",
        data: {"node1":node1,"node2":node2,"open":true},  
        dataType:"json",  
        async:false,  
        cache:false,  
        success: function(result){
        },
        error:function(){alert("ok");}
    });
}

function calculate() {
	var begin = parseInt(document.getElementsByName("start").innerHTML);
	var end = parseInt(document.getElementsByName("end").innerHTML);
	document.getElementById("bestRoute").innerHTML = "The best route is 3 -> 5 -> 4 -> 6";
	$.ajax({  
        type: "POST",   
        contentType:"application/json;charset=UTF-8",
        url:"../WebRoot/calculate.json",
        data: {"begin":begin,"end":end,"open":false},  
        dataType:"json",  
        async:false,  
        cache:false,  
        success: function(result){
        	document.getElementById("bestRoute").innerHTML = result; 
        },
        error:function(){}
    });
}