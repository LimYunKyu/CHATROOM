
struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;

};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;

};


VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;
    output.pos = float4(input.pos,1.f);
    //float4(output.pos, 1.0f);
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS_Main(VS_OUT input) : SV_Target
{
    return float4(1.0f, 1.0f, 0.0f, 1.0f);    // Yellow, with Alpha = 1
}
