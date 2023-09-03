using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class coinBar : MonoBehaviour
{
    public Slider slider;
    public Image fill;
    public Image check;
    public int advancegold;
    public void setvalue(int curvalue){
        slider.value = curvalue;
        if(curvalue >= advancegold){
            check.enabled = true;
        }
        else{
            check.enabled = false;
        }
        //fill.color = gradient.Evaluate(slider.normalizedValue);
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
