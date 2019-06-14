<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
			<form name="form1" method="POST" action="confirmlogindata.jsp">
			<table width=100% border=0 cellpadding="1" cellspacing="0">
			<tr>
				<td>
					<jsp:include page="top.jsp" flush="false"/>
				</td>
			</tr>
			<tr>
				<td><h2>로그인</h2><hr></td>
			</tr>
			<tr>
				<td><img src="image/loginnotice.png" width="100%"/></td>
			</tr>
			<tr>
				<td>
					유저명 <input type="text" name="username"/>
				</td>
			</tr>
			<tr>
				<td>
					패스워드<input type="text" name="userpasswd"/>
				</td>
			</tr>
			<tr>
				<td colspan=2>
					<input type="submit" value="ID 로그인"/>
				</td>
			</tr>
			<tr>
				<td><img src="image/notice2.png" width="100%"></td>
			</tr>
			</table>
			</form>
		</h2>
</body>
</html>