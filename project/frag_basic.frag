#version 330
in float passVoltage;
in float passLightValue;

out vec4 finalColor;

void main()
{
   finalColor = vec4(1.0, 1.0, 1.0, 1.0) * passLightValue * .75 * passVoltage;
}
