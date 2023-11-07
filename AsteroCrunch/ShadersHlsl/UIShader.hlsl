Texture2D tex : register(t0);

SamplerState pointWarp : register(s0);

cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
    float4 gColor;
};

cbuffer cbPerPass : register(b1)
{
    float4x4 gViewProj;
};

struct VertexIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float4 PosH : SV_Position;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    // Transform to homogeneous clip space.
    float4 temp = mul(float4(vin.Pos, 1.0f), gWorld);
    vout.PosH = mul(temp, gViewProj);
    vout.Color = gColor;
    vout.TexCoord = vin.TexCoord;
    return vout;
};

float4 PS(VertexOut pin) : SV_Target
{
    float4 pixel = tex.Sample(pointWarp, pin.TexCoord);
    
    if (pixel.x <= 0.05
        && pixel.y <= 0.05
        && pixel.z <= 0.05)
        discard;
    
    return pixel;
};