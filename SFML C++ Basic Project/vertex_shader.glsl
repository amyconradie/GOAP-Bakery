//varying out vec4 vert_pos;
//
//void main()
//{
//	// transform the vertex position
//	vert_pos = gl_ModelViewProjectionMatrix * gl_Vertex;
//	gl_Position = gl_ModelViewProjectionMatric * gl_Vertex;
//
//	// transform the texture coordinates
//	gl_texCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
//
//	// forward the vertex color
//	gl_FrontColor = gl_Color;
//}