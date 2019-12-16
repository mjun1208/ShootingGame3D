// It use the layer fog value
float4x4 matWorldViewProj;
float4x4 matWorldView;
float4x4 matWorld;
float4 fFog;
float4 vCamera;
float4 colorFog;

struct VS_INPUT
{
	float4 Position     : POSITION;
	float3 Diffuse   : COLOR0;
	float2 Tex0         : TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 Position     : POSITION;
	float3 Diffuse   : COLOR;
	float3 FogVal   : COLOR1;
	float2 Tex0     : TEXCOORD0;
	float  Fog : FOG;
};
struct PS_OUTPUT
{
	float4 Color: COLOR;
};
uniform sampler2D baseTexture;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// exp2 fog program
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void exp2_main_vs(in const VS_INPUT Input, out VS_OUTPUT Out)
{
	float4  clpPos, worldPos;
	// Init output
	Out = (VS_OUTPUT)0;
	// Calculate the clip space position
	clpPos = mul(Input.Position, matWorldViewProj);
	Out.Position = clpPos;
	// Simply pass on the texture coords and the vertex color
	Out.Tex0.xy = Input.Tex0.xy;
	Out.Diffuse = Input.Diffuse;
	// Extract the fog parameters
	float fDensity = fFog.x;
	float fFogEnd = fFog.y;
	// Calculate the vertex position in world space
	worldPos = mul(Input.Position, matWorld);
	// Calculate the distance to the viewer in world space
	float fDistance = distance(worldPos, vCamera);
	// The distance is scaled to have a value of 4 at distance: FogEnd
	float fDist = fDistance / fFogEnd * 4;
	// Exp squared calculation
	float f = exp(-(fDist*fDensity)*(fDist*fDensity));
	// Set the fog value
	Out.FogVal.x = f; // Passed to PixelShader using color register
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// It use the layer fog shader program
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void layer_main_vs(in const VS_INPUT Input, out VS_OUTPUT Out)
{
	float4 clpPos, camPos, worldPos;
	float  fDistance;
	// Init output
	Out = (VS_OUTPUT)0;
	// Calculate the clip space position
	clpPos = mul(Input.Position, matWorldViewProj);
	Out.Position = clpPos;
	// Simply pass on the texture coords and the vertex color
	Out.Tex0.xy = Input.Tex0.xy;
	Out.Diffuse = Input.Diffuse;

	// Get fog parameter
	float fFogTop = fFog.x;
	float fFogEnd = fFog.y;
	float fFogRange = fFog.z;
	// Calculate the world position
	worldPos = mul(Input.Position, matWorld);
	// Calculate the distance to the viewer
	fDistance = distance(worldPos, vCamera);

	// Project both points into the x-z plane
	float4 vCameraProj, vWorldProj;
	vCameraProj = vCamera;
	vCameraProj.y = 0;
	vWorldProj = worldPos;
	vWorldProj.y = 0;
	// Scaled distance calculation in x-z plane
	float fDeltaD = distance(vCameraProj, vWorldProj) / fFogEnd * 2.0f;
	// Height based calculations
	float fDeltaY, fDensityIntegral;
	if (vCamera.y > fFogTop)
	{
		if (worldPos.y < fFogTop)
		{
			fDeltaY = (fFogTop - worldPos.y) / fFogRange * 2;
			fDensityIntegral = (fDeltaY * fDeltaY * 0.5f);
		}
		else
		{
			fDeltaY = 0.0f;
			fDensityIntegral = 0.0f;
		}
	}
	else
	{
		if (worldPos.y < fFogTop)
		{
			float fDeltaA = (fFogTop - vCamera.y) / fFogRange * 2;
			float fDeltaB = (fFogTop - worldPos.y) / fFogRange * 2;
			fDeltaY = abs(fDeltaA - fDeltaB);
			fDensityIntegral = abs((fDeltaA * fDeltaA * 0.5f) - (fDeltaB * fDeltaB * 0.5f));
		}
		else
		{
			fDeltaY = abs(fFogTop - vCamera.y) / fFogRange * 2;
			fDensityIntegral = abs(fDeltaY * fDeltaY * 0.5f);
		}
	}
	float fDensity;
	if (fDeltaY != 0.0f)
	{
		fDensity = (sqrt(1.0f + ((fDeltaD / fDeltaY) * (fDeltaD / fDeltaY)))) * fDensityIntegral;
	}
	else
		fDensity = 0.0f;
	float f = exp(-fDensity);
	// Set the fog value
	Out.FogVal.x = f;   // Passed to PixelShader using color register
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main_fs(in const VS_OUTPUT Input, out PS_OUTPUT Out)
{
	// Init output
	Out = (PS_OUTPUT)0;
	// Retrieve base texture
	float4 colorBase = tex2D(baseTexture, Input.Tex0);

	// Fog blending
	float f = Input.FogVal.x;
	Out.Color = lerp(colorFog, colorBase, f);
}

int Color;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// technique
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
technique FOG
{

	// use a linear fog
	pass P0
	{
		//
		// Set Misc render states.
		pixelshader = null;
		vertexshader = null;
		fvf = XYZ | Normal;
		Lighting = true;
		NormalizeNormals = true;
		SpecularEnable = false;
		//
		// Fog States
		FogVertexMode = LINEAR; // linear fog function
		FogStart = float(fFog.x);  // fog starts 50 units away from viewpoint
		FogEnd = float(fFog.y); // fog ends 300 units away from viewpoint
		FogColor = int(Color); // gray
		FogEnable = true;       // enable
	}
	// use a exp log fog
	pass P1
	{
		vertexshader = compile vs_1_1 exp2_main_vs();
		pixelshader = compile ps_2_0 main_fs();
	}
	// use a layer shader fog
	pass P2
	{
		vertexshader = compile vs_1_1 layer_main_vs();
		pixelshader = compile ps_2_0 main_fs();
	}
}