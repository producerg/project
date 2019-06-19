<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Main page</title>
</head>
<body>
	<table width="100%" border="0" cellpadding="1" cellspacing="0">
		<tr>
			<td>
				<a href="loginpage.jsp">로그인</a>
			</td>
			<td>
				인증센터 
			</td>
			<td>
				<a href="signin_page.jsp">회원 가입</a>
			</td>
		</tr>
		<tr bgcolor="0F77BC" >
			<td>
				<font color="WHITE">금융상품</font>
			</td>
			<td>	
				<a href="https://bank.shinhan.com/index.jsp#020100000000">
				<img src="image/account.png" width=60 height=60/></a>
			</td>
			<td>
				<a href="https://bank.shinhan.com/index.jsp#020400000000">
				<img src="image/funds.png" width=60 height=60/></a>
			</td>
			<td>	
				<a href="https://bank.shinhan.com/index.jsp#020300000000">
				<img src="image/loan.png" width=60 height=60/></a>
			</td>
			<td>
				<a href="https://bank.shinhan.com/index.jsp#020500000000">
				<img src="image/coin.png" width=60 height=60/></a>
			</td>
			<td>
				<a href="https://bank.shinhan.com/index.jsp#020600000000">
				<img src="image/pension.png" width=60 height=60/></a>
			</td>
		</tr>
		<tr bgcolor="0F77BC">
			<td>
			</td>
			<td>
				<font color="WHITE">예금</font>
			</td>
			<td><font color="WHITE">펀드</font></td><td><font color="WHITE">대출</font></td>
			<td><font color="WHITE">외환</font></td><td><font color="WHITE">연금</font></td>
		</tr>
		<tr>
			<jsp:include page="recom.jsp" flush="false"/>
		</tr>
	</table>
</body>
</html>