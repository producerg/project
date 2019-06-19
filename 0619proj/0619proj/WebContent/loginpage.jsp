<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="webproj.bank.*" %>
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
				<td>
					이용자 ID <input type="text" name="mem_accid"/>
				</td>
			</tr>
			<tr>
				<td>
					비밀번호 <input type="text" name="mem_passwd"/>
				</td>
			</tr>
			<tr>
				<td colspan=2>
					<input type="submit" value="로그인"/>
				</td>
			</tr>
			<td align="left">
				<a href="#">아이디 찾기</a>
				<a href="#">비밀번호 재설정</a>
				<a href="#">회원가입</a>
			</td>
						<tr>
				<td><img src="image/loginnotice.png" width="100%"/></td>
			</tr>
			<tr>
				<td><img src="image/notice2.png" width="100%"></td>
			</tr>
			</table>
			</form>
		</h2>
</body>
</html>