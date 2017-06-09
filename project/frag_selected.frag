#version 330
in float passLightValue;

out vec4 finalColor;

void main()
{
   finalColor = vec4(1.0, 1.0, 1.0, 1.0) * passLightValue * vec4(0.7, 0.7, 1.0, 1.0);
}
