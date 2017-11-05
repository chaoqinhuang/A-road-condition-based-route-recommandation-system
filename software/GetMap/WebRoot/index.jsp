<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Decide your route</title>
    <link href="css/reset.css" rel="stylesheet">
    <link href="css/Main.css" rel="stylesheet">
    <script src="js/Main.js"></script>
    <script src="http://code.jquery.com/jquery-1.10.1.min.js"></script>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
  </head>
  
  <body>
  <div id="title">
  <br><p id=maintitle>A Road Condition Based Route Recommandation System</p>
  </div>
    <div id="map">
</div>
<form name="data">
    <label>Begin：</label>
    <input type="text" name="start"/>
    <label>End：</label>
    <input type="text" name="end" />
</form>
<br>
<div>
    <button id="getRoute" onclick="calculate()">Calculate route</button>
    <br><br>
    <label>node1:</label><input type="number" name="node1">
    <label>node2:</label><input type="number" name="node2">
    <br><br>
    <button id="addWeight" onclick="addWeight()">Add Weight</button>
    <br>
    <p id="bestRoute">
    </p>
</div>
  </body>
</html>
