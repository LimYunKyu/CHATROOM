



cbuffer TRANSFORM_PARAMS : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProjection;
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
};

cbuffer MATERIAL_PARAMS : register(b1)
{
    
    int     g_tex_on_0;
    int     g_tex_on_1;
    int     g_tex_on_2;
    int     g_tex_on_3;   
};



Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);


SamplerState g_sam_0 : register(s0);




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
   
    //1 오른쪽바라볼때
    //0 왼쪽바라볼때
    if (g_tex_on_0 == 1)
    {
        output.uv = input.uv;
        
    }
    else
    {
        input.pos.x = input.pos.x - 0.2f;
        output.uv = float2(1 - input.uv.x, input.uv.y);

    }
    output.pos = mul(float4(input.pos, 1.f), g_matWVP);
    //float4(output.pos, 1.0f);
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS_Main(VS_OUT input) : SV_Target
{
     float4 color = float4(0.f, 0.f, 0.f, 1.f);
    
     color = g_tex_0.Sample(g_sam_0, input.uv);

     clip(color.a - 0.1f);

    
    return color;

}
