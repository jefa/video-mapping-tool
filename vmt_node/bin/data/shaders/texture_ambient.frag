uniform sampler2D tex;
uniform vec2 texCorrection;
uniform vec4 color;

void main()
{
	vec2 coords = gl_TexCoord[0].st * texCorrection;
	gl_FragColor = color * texture2D(tex, coords);
}
