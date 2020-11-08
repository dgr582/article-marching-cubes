//DKE Green | 2020 | https://www.dgr582.com
//https://www.dgr582.com/articles/2020/marching-cubes

//Note that this is NOT an ideal way of setting up your shaders.
//This is just a demo. It is better to define shaders in (non-C++) files and read from these files.

#ifndef SHADERSDEFINITIONS_H
#define SHADERSDEFINITIONS_H

namespace dgr582
{
	const char* marchingCubesVertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 vPosition;\n"
		"layout (location = 1) in vec3 vNormal;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec3 normal;\n"
		"out vec3 fragPos;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = projection*view*model*vec4(vPosition, 1.0);\n"
		"    fragPos = vec3(model * vec4(vPosition, 1.0));\n"
		"    normal = vNormal;\n"
		"}\0";

	const char* marchingCubesFragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec3 lightPos;\n"
		"uniform vec3 viewPos;\n"
		"uniform vec3 lightColor;\n"
		"uniform vec3 objectColor;\n"
		"in vec3 fragPos;\n"
		"in vec3 normal;\n"
		"void main()\n"
		"{\n"
		"    // ambient\n"
		"    float ambientStrength = 0.4;\n"
		"    vec3 ambient = ambientStrength * lightColor;\n"
		"    \n"
		"    // diffuse\n"
		"    vec3 norm = normalize(normal);\n"
		"    vec3 lightDir = normalize(lightPos - fragPos);\n"
		"    float diff = max(dot(norm, lightDir), 0.0);\n"
		"    vec3 diffuse = diff * lightColor;\n"
		"    \n"
		"    // specular\n"
		"    float specularStrength = 0.8;\n"
		"    vec3 viewDir = normalize(viewPos - fragPos);\n"
		"    vec3 reflectDir = reflect(-lightDir, norm);\n"
		"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
		"    vec3 specular = specularStrength * spec * lightColor;\n"
		"    \n"
		"    vec3 result = (ambient + diffuse + specular) * objectColor;\n"
		"    FragColor = vec4(result, 1.0);\n"
		"}\n\0";


	const char* lightSourceVertexShaderSource = "#version 430 core\n"
		"layout (location = 0) in vec3 vPosition;\n"
		"layout (location = 1) in vec3 vNormal;\n"
		"layout (location = 2) in vec2 vTexCoords;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec3 normal;\n"
		"out vec3 fragPos;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = projection*view*model*vec4(vPosition, 1.0);\n"
		"    fragPos = vec3(model * vec4(vPosition, 1.0));\n"
		"    normal = vNormal;\n"
		"}\0";


	const char* lightSourceFragmentShaderSource = "#version 430 core\n"
		"out vec4 FragColor;\n"
		"uniform vec3 lightColor;\n"
		"in vec3 fragPos;\n"
		"in vec3 normal;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(lightColor, 1.0f);\n"
		"}\n\0";
}

#endif //SHADERSDEFINITIONS_H
