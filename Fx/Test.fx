float4x4 m_World;
float4x4 m_View;
float4x4 m_Proj;
sampler2D DiffuseSampler;
float4 gWorldLightPosition;
float4 gWorldCameraPosition;
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


technique BoSoo {
	pass p0 {
		vertexshader = compile vs_2_0 vs_main();
		pixelshader = compile ps_2_0 ps_main();
	}
	//pass°¡ ¿©·¯°³ - MultiPassRendering
}
