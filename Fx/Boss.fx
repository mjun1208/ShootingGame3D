float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjectionMatrix;
float Alpha;
sampler2D DiffuseSampler;
sampler2D DiffuseSampler2;

struct VS_INPUT
{
	float4 mPosition : POSITION;
	float2 mTexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition : POSITION;
	float2 mTexCoord : TEXCOORD0;
};

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, gWorldMatrix);
	Output.mPosition = mul(Output.mPosition, gViewMatrix);
	Output.mPosition = mul(Output.mPosition, gProjectionMatrix);

	Output.mTexCoord = Input.mTexCoord;

	return Output;
}

struct PS_INPUT
{
	float2 mTexCoord : TEXCOORD0;
};


float4 ps_main(PS_INPUT Input) : COLOR
{
	float4 albedo = tex2D(DiffuseSampler, Input.mTexCoord);
	return float4(albedo.r, albedo.g, albedo.b, albedo.a);
}

technique Boss {
	pass p0 {
		vertexshader = compile vs_2_0 vs_main();
		pixelshader = compile ps_2_0 ps_main();
	}
	//pass가 여러개 - MultiPassRendering
}