using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HexGenerator : MonoBehaviour
{
    [SerializeField] private GameObject _hexGameObject;
    public int _width = 14;
    public int _length = 14;
    private Vector3 _pivot = new Vector3(0.5f, 0.5f, 0.5f);
    private Bounds _bounds;


    private float _size = 1.0f;
    private float _tileXOffSet = 1.0f;
    private float _tileYOffSet = 0.0f;
    private float _tileZOffSet = 0.865f;

    public bool SpawnRect = true;
    public bool BoundToCollider = true;
    // Start is called before the first frame update
    void Start()
    {   
        if (!_hexGameObject)
            _hexGameObject = Resources.Load<GameObject>("Prefabs/Hex_1m");

        _bounds = GetComponent<Collider>().bounds;

        if(SpawnRect)
            CreateRectHexMap();
        else
            CreateHexagonalHexMap();
    }

    // Update is called once per frame
    public void CreateRectHexMap()
    {
        _tileXOffSet = _size;
        _tileZOffSet = (Mathf.Sqrt(3) * _size);

        float tileXmax = _width  * _pivot.x;
        float tileZmax = (_length - _tileZOffSet) * _pivot.z;

        for (float x = 0; x < _width; x++)
        {
            for (float z = 0; z < _length; z++)
            {
                

                Vector3 pos = (int)z % 2 == 0 ?
                    new Vector3(x * _tileXOffSet - tileXmax, 0 * _tileYOffSet, z * (_tileZOffSet / 2) - tileZmax) : new Vector3(x * _tileXOffSet + (_tileXOffSet / 2) - tileXmax, 0 * _tileYOffSet, z * (_tileZOffSet / 2) - tileZmax);


                float dist = Vector3.Distance(pos, transform.position);
                if (dist >= _bounds.size.x / 2 && BoundToCollider)
                {
                    continue;
                }
                GameObject hex = Instantiate(_hexGameObject, transform);
                SetHexagonTile(hex, pos, x, z);

            }
        }
    }

    

    public void CreateHexagonalHexMap()
    {
        GameObject hex = Instantiate(_hexGameObject, transform);
        hex.name = "Hex:" + 0 + "x" + 0;

        _tileZOffSet = (Mathf.Sqrt(3) * _size);
        for (int x = 1; x < _width / 2; x++)
        {
            var maxHex = 360 / (60 / x);
            for (int index = 1; index <= 6; index++)
            {
                    //Spawn Hexagon points
                    int angle = (60 * index) + 30;
                    Vector3 pos = new Vector3();
                    pos = PositionAroundCircle(angle * (Mathf.PI / 180), x);

                    int xindex = pos.x > 0 ? x : -x;
                    int zindex = 0;
                    if (index != 1 && index != 4)
                        zindex = pos.z > 0 ? x : -x;

                float dist = Vector3.Distance(pos, transform.position);
                //if (dist >= _bounds.size.x / 2 && BoundToCollider)
                //{
                //    continue;
                //}
                //hex = Instantiate(_hexGameObject, transform);
                //SetHexagonTile(hex, pos, xindex, zindex);

                if (dist < _bounds.size.x / 2 /*&& !BoundToCollider*/)
                {
                    hex = Instantiate(_hexGameObject, transform);
                    SetHexagonTile(hex, pos, xindex, zindex);
                }



                //Spawn Hexagon line
                for (int i = 1; i < maxHex / 6; i++)
                {
                    var side = (2 + index - 1) % 6;
                    Vector3 newPos = HexCorners(pos, i, side, false);

                    zindex = pos.z > 0 ? i : -i;

                    dist = Vector3.Distance(newPos, transform.position);
                    if (dist < _bounds.size.x / 2 /*&& !BoundToCollider*/)
                    {
                        hex = Instantiate(_hexGameObject, transform);
                        SetHexagonTile(hex, newPos, xindex, zindex);
                    }
                    
                }
            }
        }
    }

    public static Vector3 HexCorners(Vector3 center, float size, int sideIndex, bool isPointyHex = true)
    {
        var angleDeg = 60 * sideIndex + ((isPointyHex == false) ? 0 :  30);
        var angleRad = Mathf.PI / 180 * angleDeg;
        return new Vector3(center.x + size * Mathf.Cos(angleRad), 0, center.z + size * Mathf.Sin(angleRad));
    }
   

    public static Vector3 PositionAroundCircle(float rad, float radius)
    {
        float x = radius * Mathf.Sin(rad);
        float y = 0;
        float z = radius * Mathf.Cos(rad);
        return new Vector3(x, y, -z);
    }

    private static void SetHexagonTile(GameObject obj, Vector3 pos)
    {
        obj.transform.localPosition = pos;
    }

    private static void SetHexagonTile(GameObject obj, Vector3 pos, float xIndex, float zIndex)
    {
        obj.name = "Hex:" + Mathf.RoundToInt(xIndex).ToString() + "x" + Mathf.RoundToInt(zIndex).ToString();
        obj.transform.localPosition = pos;
    }

    public void SetTileInfo()
    {

    }
}
