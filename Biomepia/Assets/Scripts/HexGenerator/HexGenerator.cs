using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HexGenerator : MonoBehaviour
{
    [SerializeField] private GameObject _hexGameObject;
    public Vector2Int RectSize = new Vector2Int(10, 10);
    public int HexRadius = 14;
    public List<Color> HeighColors;

    public Texture2D HeightMap;

    private Vector3 _pivot = new Vector3(0.5f, 0.5f, 0.5f);

    private Bounds _bounds;

    private float _size = 1.0f;
    private float _tileXOffSet = 1.0f;
    private float _tileYOffSet = 0.0f;
    private float _tileZOffSet = 0.865f;

    public bool IsGenerateRect = true;
    public bool IsOnlyInsideCollidor = false;
    // Start is called before the first frame update
    void Start()
    {
        GenerateMap();
    }

    public void GenerateMap()
    {
        GetHeightFromTexture();
        while (transform.childCount > 0)
        {
            Helper.SafeDestroy(transform.GetChild(0).gameObject);
        }

        if (!_hexGameObject)
            _hexGameObject = Resources.Load<GameObject>("Prefabs/Hex_1m");

        if (GetComponent<Collider>())
        {
            _bounds = GetComponent<Collider>().bounds;
            if(_bounds.size.x <= 1 || _bounds.size.z <= 1)
                IsOnlyInsideCollidor = false;
        }
        else
            IsOnlyInsideCollidor = false;


        if (IsGenerateRect)
            CreateRectHexMap();
        else
            CreateHexagonalHexMap();

        var mat = new Material(transform.GetChild(0).GetComponent<MeshRenderer>().sharedMaterial);
        for (int i = 0; i < HeighColors.Count; i++)
        {
            var newMat = Material.Instantiate(mat);
            newMat.name = HeighColors[i].ToString();
            newMat.SetColor("_BaseColor", HeighColors[i]);
            transform.GetChild(i).GetComponent<MeshRenderer>().sharedMaterial = newMat;
            transform.GetChild(i).position = new Vector3(transform.GetChild(i).position.x, HeighColors[i].grayscale, transform.GetChild(i).position.z);
        }
    }

    // Update is called once per frame
    public void CreateRectHexMap()
    {
        _tileXOffSet = _size;
        _tileZOffSet = (Mathf.Sqrt(3) * _size);

        float tileXmax = RectSize.x * _pivot.x - 0.25f;
        float tileZmax = RectSize.y * _pivot.z - 1.25f;

        for (float x = 0; x < RectSize.x; x++)
        {
            for (float z = 0; z < RectSize.y; z++)
            {
                

                Vector3 pos = (int)z % 2 == 0 ?
                    new Vector3(x * _tileXOffSet - tileXmax, 0 * _tileYOffSet, z * (_tileZOffSet / 2) - tileZmax) : new Vector3(x * _tileXOffSet + (_tileXOffSet / 2) - tileXmax, 0 * _tileYOffSet, z * (_tileZOffSet / 2) - tileZmax);

                pos = new Vector3(Mathf.Round(pos.x * 1000.0f) / 1000.0f, 0, Mathf.Round(pos.z * 1000.0f) / 1000.0f);

                float dist = Vector3.Distance(pos, transform.position);

                if (IsOnlyInsideCollidor)
                {
                    //if (dist < _bounds.size.x / 2)
                    if (_bounds.Contains(pos))
                    {
                        GameObject hex = Instantiate(_hexGameObject, transform);
                        //_collider.
                        SetHexagonTile(hex, pos, x, z);
                    }
                }
                else
                {
                    GameObject hex = Instantiate(_hexGameObject, transform);
                    SetHexagonTile(hex, pos, x, z);
                }

            }
        }
    }


    
    public void CreateHexagonalHexMap()
    {
        GameObject hex = Instantiate(_hexGameObject, transform);
        hex.name = "Hex:" + 0 + "x" + 0;

        _tileZOffSet = (Mathf.Sqrt(3) * _size);
        for (int x = 1; x <= HexRadius; x++)
        {
            var maxHex = 360 / (60 / x);
            for (int index = 1; index <= 6; index++)
            {
                //Spawn Hexagon points
                int angle = (60 * index) + 30;
                Vector3 pos = new Vector3();
                pos = PositionAroundCircle(angle * (Mathf.PI / 180), x);
                pos = new Vector3(Mathf.Round(pos.x * 1000.0f) / 1000.0f, 0, Mathf.Round(pos.z * 1000.0f) / 1000.0f);

                int xIndex = pos.x > 0 ? x : -x;
                    int zindex = 0;

                    if (index != 1 && index != 4)
                        zindex = pos.z > 0 ? x : -x;

                float dist = Vector3.Distance(pos, transform.position);

                if (IsOnlyInsideCollidor)
                {
                    if (_bounds.Contains(pos))
                    {
                        hex = Instantiate(_hexGameObject, transform);
                        SetHexagonTile(hex, pos, xIndex, zindex);
                    }
                }
                else
                {
                    hex = Instantiate(_hexGameObject, transform);
                    SetHexagonTile(hex, pos, xIndex, zindex);
                }

                //Spawn Hexagon line
                for (int i = 1; i < maxHex / 6; i++)
                {
                    var side = index + 1 % 6;
                    Vector3 newPos = HexCorners(pos, i, side, false);
                    newPos = new Vector3(Mathf.Round(newPos.x * 1000.0f) / 1000.0f, 0, Mathf.Round(newPos.z * 1000.0f) / 1000.0f);

                    zindex = pos.z > 0 ? i : -i;

                    dist = Vector3.Distance(newPos, transform.position);
                    if (IsOnlyInsideCollidor)
                    {
                        if (_bounds.Contains(newPos))
                        {
                            hex = Instantiate(_hexGameObject, transform);
                            SetHexagonTile(hex, newPos, xIndex, zindex);
                        }
                        
                    }
                    else
                    {
                        hex = Instantiate(_hexGameObject, transform);
                        SetHexagonTile(hex, newPos, xIndex, zindex);
                    }
                }
            }
        }
    }

    public static Vector3 HexCorners(Vector3 center, float size, int sideIndex, bool isPointyHex = true)
    {
        float angleDeg = 60 * sideIndex + ((isPointyHex == false) ? 0 :  30);
        float angleRad = Mathf.PI / 180 * angleDeg;
        return new Vector3(center.x + size * Mathf.Cos(angleRad), 0, center.z + size * Mathf.Sin(angleRad));
    }
   

    public static Vector3 PositionAroundCircle(float rad, float radius)
    {
        float x = radius * Mathf.Sin(rad);
        float y = 0;
        float z = radius * Mathf.Cos(rad);
        return new Vector3(x, y, -z);
    }

    //public static bool ContainsPoint(Vector2[] polyPoints, Vector2 p)
    //{
    //    var j = polyPoints.Length - 1;
    //    var inside = false;
    //    for (int i = 0; i < polyPoints.Length; j = i++)
    //    {
    //        var pi = polyPoints[i];
    //        var pj = polyPoints[j];
    //        if (((pi.y <= p.y && p.y < pj.y) || (pj.y <= p.y && p.y < pi.y)) &&
    //            (p.x < (pj.x - pi.x) * (p.y - pi.y) / (pj.y - pi.y) + pi.x))
    //            inside = !inside;
    //    }
    //    return inside;
    //}

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

    void GetHeightFromTexture()
    {
        if(!HeightMap) return;
        float HexPixelxSize = HeightMap.width / RectSize.x;
        float HexPixelySize = HeightMap.height / RectSize.y;

        float xPixelOffSet = HexPixelxSize;
        float yPixelOffSet = (Mathf.Sqrt(3) * HexPixelxSize);
        HeighColors = new List<Color>();
        for (int x = 0; x < RectSize.x; x++)
        {
            for (int z = 0; z < RectSize.y; z++)
            {
                Vector2 pos = (int)z % 2 == 0 ?
                    new Vector2(x * xPixelOffSet, z * (yPixelOffSet / 2)) : new Vector2(x * xPixelOffSet + (xPixelOffSet / 2), z * (yPixelOffSet / 2));


                var u = pos.x / HeightMap.width;
                var v = pos.y / HeightMap.height;

                Color col = GetAverageRgbCircle(Mathf.RoundToInt(pos.x), Mathf.RoundToInt(pos.y), (int)HexPixelxSize);
                HeighColors.Add(col);
            }
        }
    }


    Color GetAverageRgbCircle(int x, int y, int radius)
    {
        return GetAverageRgbCircle(HeightMap, x, y, radius);
    }

    Color GetAverageRgbCircle(Texture2D img, int x, int y, int radius)
    {
        float r = 0;
        float g = 0;
        float b = 0;
        int num = 0;
        /* Iterate through a bounding box in which the circle lies */
        for (int i = x - radius; i < x + radius; i++)
        {
            for (int j = y - radius; j < y + radius; j++)
            {
                /* If the pixel is outside the canvas, skip it */
                if (i < 0 || i >= img.width || j < 0 || j >= img.height)
                    continue;

                /* If the pixel is outside the circle, skip it */
                if(Vector2.Distance(new Vector2(x , y), new Vector2(i, j)) > radius)
                    continue;


                /* Get the color from the image, add to a running sum */
                Color c = img.GetPixel(x, y);
                /* Sum the squares of components instead */
                r += c.r * c.r;
                g += c.g * c.g;
                b += c.b * c.b;
                num++;
            }
        }
        /* Return the sqrt of the mean of squared R, G, and B sums */
        return new Color(Mathf.Sqrt(r / num), Mathf.Sqrt(g / num), Mathf.Sqrt(b / num));
    }

}
