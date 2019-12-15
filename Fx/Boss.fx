float4x4 matWorldView;
float4x4 matWorldViewIT;
float4x4 matProjection;
float3 LightDir;
float4 diffuseColor;
float4 ambientColor;
float4 GlowColor;
float4 GlowAmbient;
float GlowThickness;
texture base;
texture UVAnime;

sampler2D Texture0 = sampler_state
{
	texture = (base);
	minfilter = LINEAR;
	magfilter = LINEAR;
	mipfilter = LINEAR;
	addressu = wrap;
};

struct VS_INPUT
{
	float4 Position : POSITION0;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 Position : POSITION0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;

};
struct VS_INPUT01
{
	float4 Position : POSITION0;
	float3 Normal : NORMAL;

};

struct VS_OUTPUT01
{
	float4 Position : POSITION0;
	float4 Diffuse : COLOR0;

};


struct PS_OUTPUT {
	float4 Diffuse : COLOR;
	float2 TexCoord : TEXCOORD0;
};
struct PS_INPUT01
{
	float4 Position : POSITION0;
	float4 Diffuse : COLOR0;

};

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	float3 L = normalize(LightDir);
	float3 P = mul(Input.Position, matWorldView);
	float3 N = normalize(mul(Input.Normal, (float3x3)matWorldViewIT));  //Normal Vector is 3x3 --> dp3

	Output.Position = mul(float4(P, 1), matProjection);
	Output.Diffuse = max(0, dot(N, L));
	Output.TexCoord = Input.TexCoord;

	return(Output);

}


float4 ps_main(VS_OUTPUT Input) : COLOR0
{
	return(tex2D(Texture0, Input.TexCoord));
    // float4 color = tex2D(Texture0, Input.TexCoord) * Input.Diffuse * diffuseColor + ambientColor;
    // return ( color);
}

VS_OUTPUT01 vs_main01(VS_INPUT01 Input01)
{
	VS_OUTPUT01 Output01;

	//Normal (view space)
	float3 N = normalize(mul(Input01.Normal, (float3x3)matWorldViewIT));

	// Displaced postion(view space)
	float3 P = mul(Input01.Position, matWorldView) + GlowThickness * N;

	//glow axis
	float3 A = float3(0, 0, 1);
	float Power;
	Power = dot(N, A);
	Power *= Power;
	Power -= 1;
	Power *= Power;
	//Power *= Power; //pwoer =(1 - (N dot A)^2)^2 = ((N dot A)^2 -1)^2

	// Projected positsdwino
	Output01.Position = mul(float4(P, 1), matProjection);
	Output01.Diffuse = GlowColor * Power + GlowAmbient;

	return(Output01);

}

float4 ps_main01(VS_OUTPUT01 Input) : COLOR0
{
	float4 color = Input.Diffuse;
	return color;

}

//Technique
technique Boss
{
	pass P0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	
		Texture[0] = base;
	
		MinFilter[0] = LINEAR;
		MagFilter[0] = LINEAR;
		MipFilter[0] = LINEAR;
	}

	pass P0
	{
		VertexShader = compile vs_2_0 vs_main01();
		PixelShader = compile ps_2_0 ps_main01();

		Texture[0] = NULL;
		AlphaBlendEnable = TRUE;
		SrcBlend = ONE;
		DestBlend = ONE;
	}
}
