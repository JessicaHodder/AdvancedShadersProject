#version 330 core






out vec4 FragColor ;


//in vec2 TexCoords ;
//in vec3 FragPos ;




//old
//in vec3 gWorldPos_FS_in ;
//
//void main()
//{
//  FragColor = vec4(0.2,0.8,0.2,1.0) ;
//}


in vec3 gNormals ;
in vec3 gWorldPos ;





struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
};                                                                        


struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

//uniform sampler2D texture1;
uniform DirLight dirLight;
uniform Material mat ;
uniform vec3 viewPos ;

uniform int scale ;



vec4 green = vec4(0.3, 0.35, 0.15, 0.0) ;
vec4 gray = vec4(0.5, 0.4, 0.5, 0.0) ;
vec4 yellow = vec4(0.7, 0.3, 0.15, 0.0);

//vec4 green = vec4(0.1, 0.7, 0.1, 0.0) ;
//vec4 gray = vec4(0.5, 0.4, 0.5, 0.0) ;

vec3 ambientColor ;
vec3 diffuseColor ;
vec3 specularColor ;

float height = gWorldPos.y/scale;


void main()
{   
    
    if (height > 0.4)
    {
        ambientColor = vec3(mix( green, gray, smoothstep(0.3, 1.0, height)).rgb) ;
        diffuseColor = vec3(mix( green, gray, smoothstep(0.3, 1.0, height)).rgb) ;
        specularColor = vec3(mix( green, gray, smoothstep(0.3, 1.0, height)).rgb) ;

        //ambientColor = green.rgb ;
        //diffuseColor = green.rgb ;
        //specularColor = green.rgb ;
    }
    else if (height > 0)
    {
        ambientColor = vec3(mix( green, yellow, smoothstep(0.3, 1.0, height)).rgb) ;
        diffuseColor = vec3(mix( green, yellow, smoothstep(0.3, 1.0, height)).rgb) ;
        specularColor = vec3(mix( green, yellow, smoothstep(0.3, 1.0, height)).rgb) ;
    }
    else
    {
        ambientColor = mat.ambient;
        diffuseColor = mat.diffuse;
        specularColor = mat.specular ;
    }


     vec3 viewDir = normalize(viewPos - gWorldPos);
	 vec3 norm = normalize(gNormals) ;
	// vec3 ambient = dirLight.ambient * mat.ambient; 
     vec3 ambient = dirLight.ambient * ambientColor; 
     vec3 lightDir = normalize(-dirLight.direction);
    // diffuse shading
    float diff = max(dot(norm, dirLight.direction), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-dirLight.direction, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    // combine results
   
    //vec3 diffuse  = dirLight.diffuse  * (diff * mat.diffuse);
    vec3 diffuse  = dirLight.diffuse  * (diff * diffuseColor);
    //vec3 specular = dirLight.specular * (spec * mat.specular);
    vec3 specular = dirLight.specular * (spec * specularColor);
    FragColor = vec4((ambient + diffuse + specular),1.0f);

	
}
	