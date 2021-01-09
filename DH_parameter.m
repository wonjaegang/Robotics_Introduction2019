function A = DH_parameter(theta, d, a, alpha)
% cos(pi/2)가 정확히 0이 아닌 문제를 해결하기 위해, degree로 변환시켜 계산한다.
% 입력 값들은 모두 실수(rad)이다.
dtheta = rad2deg(theta);
dalpha = rad2deg(alpha);
A = [cosd(dtheta) -sind(dtheta) 0 0;sind(dtheta) cosd(dtheta) 0 0;0 0 1 0;0 0 0 1]...
*[1 0 0 0;0 1 0 0;0 0 1 d;0 0 0 1]*[1 0 0 a;0 1 0 0;0 0 1 0;0 0 0 1]...
*[1 0 0 0;0 cosd(dalpha) -sind(dalpha) 0;0 sind(dalpha) cosd(dalpha) 0;0 0 0 1];