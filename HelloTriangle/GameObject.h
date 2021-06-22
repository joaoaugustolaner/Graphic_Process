#pragma once

//Esta classe vai ir sofrendo altera��es durante o curso
//Aqui ela est� preparada apenas para sprites texturizados

#include "Shader.h"

// GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject() {}

	void initialize();
	void setTexture(int texID);
	void setShader(Shader* shader) { this->shader = shader; shader->Use(); }
	void setPosition(glm::vec3 pos) { this->pos = pos; } //dica: fazer setX e setY individualmente
	void setDimension(glm::vec3 scale) { this->scale = scale; }
	void setAngle(float angle) { this->angle = angle; } //para 3D precisa angulo por eixo ou quaternion
	//TO DO: m�todos para anima��o

	//Para controle direto da matriz de transforma��es
	void setRotation(float angle, glm::vec3 axis, bool reset = true);
	void setTranslation(glm::vec3 displacements, bool reset = true);
	void setScale(glm::vec3 scaleFactors, bool reset = true);
	
	void draw();
	void update();

protected:
	//Atributos gerais

	GLuint VAO; //ID do buffer de geometria

	glm::mat4 transform; //matriz de transforma��o

	unsigned int texID; //identificador da textura

	Shader* shader; //ponteiro para o objeto de shader, para fazer a interface


	//Atributos de controle da posi��o, orienta��o e dimens�es do sprite
	glm::vec3 pos, scale;
	float angle;

	//Atributos para controle da anima��o
	int nAnims, nFrames;
	int iAnim, iFrame; //indices da anima��o e frame atual

};

