//--------------------------------------------------------------//
// OutlineRendering
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// NormalRender
//--------------------------------------------------------------//
texture rtOrigin_Tex : RenderColorTarget
<
float2 RenderTargetDimensions = { 512,512 };
string Format = "D3DFMT_A8R8G8B8";
float  ClearDepth = 1.000000;
int    ClearColor = -16777216;
> ;
float4x4 matViewProjection : ViewProjection;
float4x4 matView : View;

struct NormalRender_VS_INPUT
{
	float4 Position : POSITION0;
	float3 Normal : NORMAL0;
};

struct NormalRender_VS_OUTPUT
{
	float4 Position : POSITION0;
	float4 NormalColor : COLOR0;
};

NormalRender_VS_OUTPUT NormalRender_vs_main(NormalRender_VS_INPUT In)
{
	NormalRender_VS_OUTPUT Out;

	Out.Position = mul(In.Position, matViewProjection);
	float3 Norm = mul(In.Normal, (float3x3)matView);
	Out.NormalColor = float4(Norm, 1.0f);

	return Out;
}

float4 Position_NormalRender_ps_main(float4 NormalColor : COLOR0) : COLOR0
{
   return NormalColor;
}




//--------------------------------------------------------------//
// OutlineRender
//--------------------------------------------------------------//
struct OutlineRender_VS_INPUT
{
	float4 Position : POSITION0;
	float3 Normal : NORMAL0;
};

struct OutlineRender_VS_OUTPUT
{
	float4 Position : POSITION0;
	float2 TexCoord : TEXCOORD0;
};

OutlineRender_VS_OUTPUT OutlineRender_vs_main(OutlineRender_VS_INPUT In)
{
	OutlineRender_VS_OUTPUT Out;

	In.Position.xy = sign(In.Position.xy);
	Out.Position = float4(In.Position.xy, 0.0f, 1.0f);

	//Image-space
	//Out.TexCoord = ( float2(In.Position.x, -In.Position.y) + 1.0f) * 0.5f;
	Out.TexCoord.x = 0.5f * (1.0f + In.Position.x);
	Out.TexCoord.y = 0.5f * (1.0f - In.Position.y);

	return(Out);
}

sampler RT = sampler_state
{
	Texture = (rtOrigin_Tex);
};

float mask[9] =
{ -1, -1, -1,
  -1, 8, -1,
  -1, -1, -1 };

float coord[3] = { -1, 0, 1 };
float divider = 1.0f;
float MAP_CX = 512.0f;
float MAP_CY = 512.0f;


float4 OutlineRender_ps_main(float2 Tex : TEXCOORD0) : COLOR0
{
   float4 color = 0;

   for (int i = 0; i < 9; i++)
	  color += mask[i] * (tex2D(RT, Tex + float2(coord[i % 3] / MAP_CX, coord[i / 3] / MAP_CY)));

   float gray = 1 - (color.r * 0.3f + color.g * 0.59f + color.b*0.11f);
   return float4(gray, gray, gray, 1) / divider;

   //return tex2D(RT, Tex);
}




//--------------------------------------------------------------//
// Technique Section for OutlineRendering
//--------------------------------------------------------------//
technique Boss
{
	pass p0
		//<
		//string Script = "RenderColorTarget0 = rtOrigin_Tex;"
		//"ClearColor = (0, 0, 0, 255);"
		//"ClearDepth = 1.000000;";
		//>
	{
		VertexShader = compile vs_2_0 NormalRender_vs_main();
		PixelShader = compile ps_2_0 Position_NormalRender_ps_main();
	}

    pass p1
    {
    	VertexShader = compile vs_2_0 OutlineRender_vs_main();
    	PixelShader = compile ps_2_0 OutlineRender_ps_main();
    }

}