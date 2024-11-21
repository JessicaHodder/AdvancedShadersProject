#include "Scene.h"

Scene::Scene(GLFWwindow* window, std::shared_ptr<InputHandler> H) : 
m_window(window),
m_handler(H)
{
	// Shader
	m_terrainShader = new Shader("..\\shaders\\plainVert.vs", "..\\shaders\\plainFrag.fs", "..\\shaders\\Norms.gs", "..\\shaders\\tessControlShader.tcs", "..\\shaders\\tessEvaluationShader.tes");



	m_heightMap = loadTexture("..\\shaders\\heightMap.jpg");
	m_terrainShader->use();

	

	//light settings
	glm::vec3 dirLightPos(.7f, .6f, .2f);
	m_terrainShader->setVec3("dirLight.direction", dirLightPos);
	m_terrainShader->setVec3("dirLight.ambient", 0.7f, 0.7f, 0.7f);
	m_terrainShader->setVec3("dirLight.diffuse", 0.75f, 0.75f, 0.75f);
	m_terrainShader->setVec3("dirLight.specular", 0.8f, 0.8f, 0.8f);
	//material properties
	m_terrainShader->setVec3("mat.ambient", 0.5, 0.5, 0.5);
	m_terrainShader->setVec3("mat.diffuse", 0.5, 0.5, 0.5);
	m_terrainShader->setVec3("mat.specular", 0.497f, 0.508f, 0.506f);
	m_terrainShader->setFloat("mat.shininess", 0.9f);
	
	// Camera & Input
	m_camera = std::make_shared<FirstPersonCamera>(glm::vec3(260, 50, 300));   // xyz argument to set starting position of camera
	m_camera->attachHandler(window, H);
	// Terrain Grid
	m_terrain = std::make_shared<Terrain>();
}

Scene::~Scene()
{
	delete m_terrainShader;
}

void Scene::update(float dt)
{
	m_camera->update(dt); // check for input

	// MVP matrices and uniforms
	// move this to a UBO
	m_projection = glm::perspective(m_camera->getFOV(), (float)SCR_WIDTH / (float)SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);  // values from properties header
	m_view = m_camera->getViewMatrix();
	m_model = glm::mat4(1.0f);
	m_terrainShader->setMat4("projection", m_projection);
	m_terrainShader->setMat4("view", m_view);
	m_terrainShader->setMat4("model", m_model);
	m_terrainShader->setVec3("viewPos", m_camera->getPosition());
	m_terrainShader->setInt("heightMap", 0);
	m_terrainShader->setInt("scale", 100);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_heightMap);
	m_terrain->render();
}

//  load texture stuff
unsigned int Scene::loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
		std::cout << "Loaded texture at path: " << path << " width " << width << " id " << textureID << std::endl;
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	return textureID;
}



