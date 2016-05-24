#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;//�������� sfml ������ "���", ������� � �������� �������

void viewmap(float time)   //������� ��� ����������� ������ �� �����. ��������� ����� sfml
{
    if (Keyboard::isKeyPressed(Keyboard::D)){
        view.move(0.1*time, 0);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
    }

    if (Keyboard::isKeyPressed(Keyboard::S)){
        view.move(0, 0.1*time);//�������� ����� ���� (�� ����, ����� �� ������� ����� - �� ���� �����)
    }

    if (Keyboard::isKeyPressed(Keyboard::A)){
        view.move(-0.1*time, 0);//�������� ����� ����� (�� ����, ����� �� ������� ����� - �� ���� �����)
    }
    if (Keyboard::isKeyPressed(Keyboard::W)){
        view.move(0, -0.1*time);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
    }

}
void changeview()
{
    if (Keyboard::isKeyPressed(Keyboard::U)){
        view.zoom(1.0100f); //������������, ����������
        //view.zoom(1.0006f); //���� ����� ����������� ��������������
    }
    if (Keyboard::isKeyPressed(Keyboard::R)){
        //view.setRotation(90);//����� �� ������ ������� ������
        view.rotate(1);//���������� ������������ ������ (������������� �������� - � �������� �������)
    }
    if (Keyboard::isKeyPressed(Keyboard::I)){
        view.setSize(640, 480);//������������� ������ ������ (��� ��������)
    }

    if (Keyboard::isKeyPressed(Keyboard::P)){
        view.setSize(540, 380);//�������� ������ ������
    }
    if (Keyboard::isKeyPressed(Keyboard::Q)){
        view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//����� ������� �������� ���������� ����� ��� ���� �� �����. ����� ������ ������� ��� ���� ������ View � ����������� � ���� ���������� ������ 2.
    }
}

#endif // VIEW_H_INCLUDED
