attribute vec2 coord2d;
void main(void) 
{

	mat4 scale = mat4 (
			0.18,	0.0,	0.0,	0.0,
			0.0,	0.18,	0.0,	0.0,
			0.0,	0.0,	0.18,	0.0,
			0.0,	0.0,	0.0,	1.0);

  gl_Position = scale * (vec4(coord2d, 0.0, 1.0) + vec4(0.0, -5.0, 0.0, 0.0));
}