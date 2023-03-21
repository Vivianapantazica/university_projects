#version 330

// Input

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform vec3 carPos;
float len;

// output values to fragment shader
out vec3 color;


void main()
{
    // send output to fragment shader
	color = object_color;

	// compute gl_Position 
	// folosim matricea model pentru a computa pozitiile tuturor vertecsilor in coordonatele lumii
	gl_Position = Model * vec4(v_position, 1.0);

	// calculam distantele dintre puncte in planul XOZ (coordonata y a punctelor va fi nula)
	len = length(vec4(vec3(carPos.x, 0, carPos.z), 1.f) - vec4(gl_Position.x, 0, gl_Position.z, gl_Position.w));

	// modificam coordonatele y pentru a realiza efectul de curbura
	gl_Position.y = gl_Position.y - pow(len, 2.0f) * 0.01f;

	// computam gl_Position final adaugand matricea de vizualizare si de proiectie (acestea nemodificate)
	gl_Position = Projection * View * gl_Position;
}
