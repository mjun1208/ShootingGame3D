float4x4 m_World;
float4x4 m_View;
float4x4 m_Proj;

//float OutLineWidth;

struct vs_output {
	float4 Position : POSITION; //시멘틱
};


vs_output vs(vs_output Input) {
	vs_output Output;

	Output.Position = mul(Input.Position, m_World);
	Output.Position = mul(Output.Position, m_View);
	//	
	Output.Position = mul(Output.Position, m_Proj);

	return Output;
	//파이프라인 구축
}

float4 ps(vs_output input) : COLOR{

	return float4(1,1,1,0.3f);
}

vs_output _vs(in float4 iPos : POSITION) {
	vs_output Output;

	Output.Position = mul(iPos, m_World);
	Output.Position = mul(Output.Position, m_View);
	Output.Position = mul(Output.Position, m_Proj);

	return Output;
}

float4 _ps(vs_output input) : COLOR{

	return float4(1,0,0,0.2f);
}

technique BoSoo {
	pass p0 {
		vertexshader = compile vs_2_0 vs();
		pixelshader = compile ps_2_0 ps();
	}

	pass p1 {
		vertexshader = compile vs_2_0 _vs();
		pixelshader = compile ps_2_0 _ps();
	}

	//pass가 여러개 - MultiPassRendering
}
