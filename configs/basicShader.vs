#version 330 core

///
/// No need for color here. Everything displayed will have a texture.
/// Position and texture loaded in via attributes because
/// they will change with each VAO.
///

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

///
/// Transformation matrices.
///

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

///
/// Variable to pass texture coordinate data to the fragment shader.
///

out vec2 texCoords;

void main()
{

  gl_Position = projection * view * model * vec4( aPos, 1.0f );
  texCoords = aTexCoords;

}