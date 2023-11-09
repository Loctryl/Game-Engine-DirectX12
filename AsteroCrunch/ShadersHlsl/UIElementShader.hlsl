Texture2D tex : register(t0);

SamplerState pointWarp : register(s0);

cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
    float4 gColor;
    float gDivider;
    int gDigit;
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
    //vout.PosH = mul(temp, gViewProj);
    vout.PosH = temp;
    
    vout.Color = gColor;
    
    float2 UV = { 0.f, 0.f };
    
    UV.y = vin.TexCoord.y;
    
    if (gDigit == 0) {
        UV.x = vin.TexCoord.x / gDivider;
    }
    else {
        if (vin.TexCoord.x == 0) {
            UV.x = (1 / gDivider) * gDigit;
        }
        else {
            UV.x = (1 / gDivider) * (gDigit + 1);
        }
    }
    
    vout.TexCoord = UV;
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