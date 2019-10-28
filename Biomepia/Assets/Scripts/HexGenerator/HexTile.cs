using System;
using UnityEngine;

namespace Assets.Scripts.HexGenerator
{
    [Serializable]
    public class Uv
    {
        public float U;
        public float V;

        public Uv()
        {
            U = 0.0f;
            V = 0.0f;
        }

        public Uv(float u = 0.0f, float v = 0.0f)
        {
            U = u;
            V = v;
        }
    }

    [Serializable]
    public class HexTile
    {
        public string Name = "HexTile";
        public Transform Transform;
        public Vector3Int Index = new Vector3Int(0,0,0);
        public Uv HeightUv = new Uv(0);
    }
}