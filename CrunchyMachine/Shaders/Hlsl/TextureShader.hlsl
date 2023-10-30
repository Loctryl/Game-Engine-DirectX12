Texture2D tex : register(t0);

SamplerState sample : register(s0);

cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
};

cbuffer cbPerPass : register(b1)
{
    float4x4 gViewProj;
};

struct VertexIn
{
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float3 PosH : Position;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    // Transform to homogeneous clip space.
    float4 temp = mul(float4(vin.Pos, 1.0f), gWorld);
    vout.PosH = mul(temp, gViewProj);
    // Just pass vertex color into the pixel shader.
    
    //vout.Color = vin.Pos;
    return vout;
};

float4 PS(VertexOut pin) : SV_Target
{
    //float4 texDiffuseAlbedo = gDiffuseMap.Sample(
    //    gsamAnisotropicWrap, pin.TexCoord);
    
    //float4 diffuseAlbedo = texDiffuseAlbedo * gDiffuseAlbedo;
    //return diffuseAlbedo;
    return float4(0.7, 1, 0.7, 1);
};