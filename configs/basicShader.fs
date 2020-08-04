#version 330 core

///
/// Defines the final output color of a fragment (pixel).
///

out vec4 FragColor;

///
/// Taken from the attribute of the vertex shader.
///

in vec2 texCoords;

///
/// The texture being displayed.
///

uniform sampler2D tex;

///
/// The ambient lighting to use.
///

uniform vec4 ambience;


void main()
{

    FragColor = ambience * texture(tex, texCoords);

}