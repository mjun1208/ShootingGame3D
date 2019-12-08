float4x4 m_World;
float4x4 m_View;
float4x4 m_Proj;
sampler2D DiffuseSampler;
float4 gWorldLightPosition;
float4 gWorldCameraPosition;

float4x4 WITM : WORLDINVERSETRANSPOSE;

float4 Alpha;
float time : TIME;
float timeangle : TIME;
sampler2D Boss_Rumble;
//float OutLineWidth;

struct vs_input {
	float4 Position : POSITION; //½Ã¸àÆ½
	float2 mTexCoord : TEXCOORD0;
	float3 mNormal : NORMAL;
};

struct vs_output {
	float4 Position : POSITION; //½Ã¸àÆ½
	float2 mTexCoord : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
	float3 mViewDir: TEXCOORD2;
	float3 mReflection: TEXCOORD3;
};

struct ps_input
{
	float2 mTexCoord : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
	float3 mViewDir: TEXCOORD2;
	float3 mReflection: TEXCOORD3;
};

vs_output vs_main(vs_input Input) {
	vs_output Output;

	Output.Position = mul(Input.Position, m_World);

	float3 lightDir = Output.Position.xyz - gWorldLightPosition.xyz;
	lightDir = normalize(lightDir);
	float3 viewDir = normalize(Output.Position.xyz - gWorldCameraPosition.xyz);
	Output.mViewDir = viewDir;

	Output.Position = mul(Output.Position, m_View);
	Output.Position = mul(Output.Position, m_Proj);

	float3 worldNormal = mul(Input.mNormal, (float3x3)m_World);
	worldNormal = normalize(worldNormal);

	//Output.mTexCoord = Input.mTexCoord;
	Output.mTexCoord = Input.mTexCoord;
	Output.mDiffuse = dot(-lightDir, worldNormal);
	Output.mReflection = reflect(lightDir, worldNormal);

	return Output;
	//ÆÄÀÌÇÁ¶óÀÎ ±¸Ãà
}

float4 ps_main(ps_input input) : COLOR{
	float3 diffuse = saturate(input.mDiffuse);

	float3 reflection = normalize(input.mReflection);
	float3 viewDir = normalize(input.mViewDir);
	float3 specular = 0;
	if (diffuse.x > 0)
	{
		specular = saturate(dot(reflection, -viewDir));
		specular = pow(specular, 20.0f);
	}

	float3 ambient = float3(0.4f, 0.4f, 0.4f);

	float4 albedo = tex2D(DiffuseSampler, input.mTexCoord);
	return float4(albedo * (ambient + diffuse + specular), 1);
}

////////////////////////////Boss


//texture
texture DiffuseTexture_1 : DIFFUSE
<
	string ResourseName = "AA.tga";
	string UIName = "Diffuse_Texture1";
	string ResourceType = "2D";
>;

sampler2D DiffuseSampler_1 = sampler_state
{
	Texture = <DiffuseTexture_1>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture DiffuseTexture_2 : DIFFUSE
<
	string ResourseName = "AA.tga";
	string UIName = "Diffuse_Texture2";
	string ResourceType = "2D";
>;

sampler2D DiffuseSampler_2 = sampler_state
{
	Texture = <DiffuseTexture_2>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture OpacityTexture : OPACITY
<
	string ResoureName = "AA.tga";
	string UIName = "Opacity_Texture";
	string ResourceType = "2D";
>;

sampler2D OpacitySampler = sampler_state
{
	Texture = <OpacityTexture>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture NormalTexture : NORMAL
<
	string ResoureName = "AA.tga";
	string UIName = "Normal_Texture";
	string ResourceType = "2D";
>;

sampler2D NormalSampler = sampler_state
{
	Texture = <NormalTexture>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

struct VS_OUTPUT
{
	float4 pposition : POSITION;
	float2 wuv : TEXCOORD0;
	float3 wnormal : TEXCOORD1;
	float3 wtangent : TEXCOORD2;
	float3 wbinormal : TEXCOORD3;
	float4 wposition : TEXCOORD4;
	float2 wuv1 : TEXCOORD5;
	float2 wuv2 : TEXCOORD6;
	float2 wuv3 : TEXCOORD7;
};

float2 rotateUV(float2 Uv, float2 Center, float Theta)
{
	float2 sc;
	sincos((Theta / 180 * 3.14159), sc.x, sc.y);
	float2 uv = Uv - 0.5;
	float2 rotateduv;
	rotateduv.x = dot(uv, float2(sc.y, -sc.x));
	rotateduv.y = dot(uv, sc.xy);
	rotateduv += 0.5;
	return rotateduv;
}

VS_OUTPUT vs_main_2(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.pposition = mul(Input.position, m_World);
	Output.pposition = mul(Output.pposition, m_View);
	Output.pposition = mul(Output.pposition, m_Proj);

	//WITM = transpose(WITM);
	Output.wnormal = mul(Input.normal, (float3x3)WITM);
	Output.wtangent = mul(Input.tangent, (float3x3)WITM);
	Output.wbinormal = mul(Input.binormal, (float3x3)WITM);
	Output.wposition = mul(Input.position, m_World);

	Output.wuv.x = Input.uv.x;
	Output.wuv.y = -Input.uv.y;
	Output.wuv1.x = Input.uv.x - time / 4;
	Output.wuv1.y = -Input.uv.y;
	Output.wuv2.y = Input.uv.x - time / 2;
	Output.wuv2.x = -Input.uv.y;
	Output.wuv3 = rotateUV(Input.uv, 0.5, timeangle * 60);

	return Output;
}

float4 ps_main_2(VS_OUTPUT Input) : COLOR
{
	float3 N = normalize(Input.wnormal);
	float3 T = normalize(Input.wtangent);
	float3 B = normalize(Input.wbinormal);

	float3 bump = 0.2 * (tex2D(NormalSampler, Input.wuv1)).rgb;
	float3 Nn = N + bump.x * T + bump.y * B;

	float3 diffuseM1 = tex2D(DiffuseSampler_1, (Input.wuv3 + Nn)); //rotateMap
	float3 diffuseM2 = tex2D(DiffuseSampler_2, (Input.wuv2 + Nn)); //up map

	float Opacity = diffuseM1.x * diffuseM2.x;

	float3 diffuse = (diffuseM1 * diffuseM2);

	return float4(1 * (diffuse), Opacity);
}

///////////////////////technique

technique Boss {
	pass p0 {
		vertexshader = compile vs_2_0 vs_main();
		pixelshader = compile ps_2_0 ps_main();
	}

	pass p1 {
		CullMode = None;

		AlphaBlendEnable = true;

		DestBlend = One;

		SrcBlend = SrcAlpha;
		vertexshader = compile vs_3_0 vs_main_2();
		pixelshader = compile ps_3_0 ps_main_2();
	}
	//pass°¡ ¿©·¯°³ - MultiPassRendering
}
