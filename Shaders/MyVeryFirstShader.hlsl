struct ConstantData
{
	float4 radius;
};

cbuffer ConstBuf: register(b0)
{
	ConstantData ConstData;
};

struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

PS_IN VSMain( VS_IN input )
{
	PS_IN output = (PS_IN)0;

	output.pos = input.pos;
	output.col = input.col;
	
	return output;
}

float4 PSMain( PS_IN input ) : SV_Target
{
	float4 col = input.col;
	if (pow(input.pos.x - 400, 2) + pow(input.pos.y - 400, 2) > pow(ConstData.radius.x,2)) 
		col = float4(1.f,0.f,0.f, 1.f);
	return col;
}