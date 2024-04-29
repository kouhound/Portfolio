using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Easing : MonoBehaviour
{
    // サイト：左から右、上から下
    //  1  2  3     4  5  6
    //  7  8  9    10 11 12
    // https://easings.net/ja
    
    private const float c1 = 1.70158f;
    private const float c2 = c1 * 1.525f;
    private const float c3 = c1 + 1;
    private const float c4 = (2 * Mathf.PI) / 3;
    private const float c5 = (2 * Mathf.PI) / 4.5f;
    private const float n1 = 7.5625f;
    private const float d1 = 2.75f;

    public float Set(float x, int i)
    {
        switch (i)
        {
            case 1://sine
                return 1 - Mathf.Cos(x * Mathf.PI / 2);
            case 2:
                return Mathf.Sin(x * Mathf.PI / 2);
            case 3:
                return -(Mathf.Cos(Mathf.PI * x) - 1) / 2;
            case 4://Quat
                return Mathf.Pow(x, 2);
            case 5:
                return 1 - Mathf.Pow(1 - x, 2);
            case 6:
                return x < 0.5f ? 2 * Mathf.Pow(x, 2) : 1 - Mathf.Pow(-2 * x + 2, 2) / 2;
            case 7://Cubic
                return Mathf.Pow(x, 3);
            case 8:
                return 1 - Mathf.Pow(1 - x, 3);
            case 9:
                return x < 0.5f ? 4 * Mathf.Pow(x, 3) : 1 - Mathf.Pow(-2 * x + 2, 3) / 2;
            case 10://Quart
                return Mathf.Pow(x, 4);
            case 11:
                return 1 - Mathf.Pow(1 - x, 4);
            case 12:
                return x < 0.5f ? 8 * Mathf.Pow(x, 4) : 1 - Mathf.Pow(-2 * x + 2, 4) / 2;
            case 13://Quint
                return Mathf.Pow(x, 5);
            case 14:
                return 1 - Mathf.Pow(1 - x, 5);
            case 15:
                return x < 0.5f ? 16 * Mathf.Pow(x, 5) : 1 - Mathf.Pow(-2 * x + 2, 5) / 2;
            case 16://Expo
                return x == 0 ? 0 : Mathf.Pow(2, 10 * x - 10);
            case 17:
                return x == 1 ? 1 : 1 - Mathf.Pow(2, -10 * x);
            case 18:
                return x == 0 ? 0 : x == 1 ? 1 : x < 0.5f ? Mathf.Pow(2, 20 * x - 10) / 2 : (2 - Mathf.Pow(2, -20 * x + 10)) / 2;
            case 19://Circ
                return 1 - Mathf.Sqrt(1 - Mathf.Pow(x, 2));
            case 20:
                return Mathf.Sqrt(1 - Mathf.Pow(x - 1, 2));
            case 21:
                return x < 0.5f
              ? (1 - Mathf.Sqrt(1 - Mathf.Pow(2 * x, 2))) / 2
                : (Mathf.Sqrt(1 - Mathf.Pow(-2 * x + 2, 2)) + 1) / 2;

            case 22://Back
                return c3 * x * x * x - c1 * x * x;

            case 23:
                return 1 + c3 * Mathf.Pow(x - 1, 3) + c1 * Mathf.Pow(x - 1, 2);

            case 24:
                return x < 0.5f
                    ? (Mathf.Pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
                    : (Mathf.Pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;

            case 25://Elastic
                return x == 0 ? 0
                    : x == 1 ? 1
                    : -Mathf.Pow(2, 10 * x - 10) * Mathf.Sin((x * 10 - 10.75f) * c4);

            case 26:
                return x == 0 ? 0
                    : x == 1 ? 1
                    : Mathf.Pow(2, -10 * x) * Mathf.Sin((x * 10 - 0.75f) * c4) + 1;

            case 27:
                return x == 0 ? 0
                    : x == 1 ? 1
                    : x < 0.5f
                    ? -(Mathf.Pow(2, 20 * x - 10) * Mathf.Sin((20 * x - 11.125f) * c5)) / 2
                    : (Mathf.Pow(2, -20 * x + 10) * Mathf.Sin((20 * x - 11.125f) * c5)) / 2 + 1;

            case 28://Bounce
                return 1 - bounce(1 - x);

            case 29:
                return bounce(x);

            case 30:
                return x < 0.5f
                    ? (1 - bounce(1 - 2 * x)) / 2
                    : (1 + bounce(2 * x - 1)) / 2;

            default:
                return x;

        }
    }

    private int bounce(float v)
    {
        throw new NotImplementedException();
    }

    float bounce(float x, float d1, float n1)
    {
        if (x < 1f / d1)
        {
            return n1 * x * x;
        }
        else if (x < 2f / d1)
        {
            x -= 1.5f / d1;
            return n1 * x * x + 0.75f;
        }
        else if (x < 2.5f / d1)
        {
            x -= 2.25f / d1;
            return n1 * x * x + 0.9375f;
        }
        else
        {
            x -= 2.625f / d1;
            return n1 * x * x + 0.984375f;
        }
    }
}

