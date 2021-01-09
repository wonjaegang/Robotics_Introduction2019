function A = DH_parameter(theta, d, a, alpha)
% cos(pi/2)�� ��Ȯ�� 0�� �ƴ� ������ �ذ��ϱ� ����, degree�� ��ȯ���� ����Ѵ�.
% �Է� ������ ��� �Ǽ�(rad)�̴�.
dtheta = rad2deg(theta);
dalpha = rad2deg(alpha);
A = [cosd(dtheta) -sind(dtheta) 0 0;sind(dtheta) cosd(dtheta) 0 0;0 0 1 0;0 0 0 1]...
*[1 0 0 0;0 1 0 0;0 0 1 d;0 0 0 1]*[1 0 0 a;0 1 0 0;0 0 1 0;0 0 0 1]...
*[1 0 0 0;0 cosd(dalpha) -sind(dalpha) 0;0 sind(dalpha) cosd(dalpha) 0;0 0 0 1];