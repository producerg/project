<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<!-- 계좌에 얼마 남았다 ㅋ 띄워줌  -->
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<table width="100%" border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td>
				<jsp:include page="top.jsp" flush="false"/> 
			</td>
			<td>
				<a href="logout.jsp">[로그아웃]</a>
			</td>
		</tr>
		<tr>
			<td>
				<b><%= session.getAttribute("username") %></b> 고객님 환영합니다.
			</td>
			<td>
				<a href="#" onClick="history.go(-1); return false;">[메인 화면으로]</a>
			</td>
		</tr>
		<tr>
			<td align=center>
				현재 <b><font size=5><%= session.getAttribute("useraccnum") %></font></b>계좌의 잔액은<br>
				<font color="469DD9" size=5><%= session.getAttribute("deposit") %> </font>원 입니다.
			</td>
		</tr>
		<tr align=center width=50%>
			<td>
				<a href="#">[거래 내역 보기]</a>
			</td>
		</tr>
		<tr align=center width=50%>
			<td>
				<a href="#">[이체하기]</a>
			</td>	
		</tr>
		<tr>
			<td>
				<jsp:include page="bottom_mainscreen.jsp" flush="false"/> 
			</td>
		</tr>		
	</table>
</body>
</html>