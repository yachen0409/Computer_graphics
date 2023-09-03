using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public int currentgold;
    public TMP_Text goldtext;
    public int currenthealth;
    public TMP_Text healthtext;
    public Slider slider;
    public TMP_Text leveltext;
    public TMP_Text noticetext;
    public int advancegold;
    public AudioSource coinsound;
    public AudioSource treasuresound;
    // Start is called before the first frame update
    void Start()
    {
        advancegold = FindObjectOfType<Finish>().returnadvancegold();
	int index = SceneManager.GetActiveScene().buildIndex;
	leveltext.text = "Level " + index;
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKeyDown("escape")){
	    Application.Quit();
        }
        if(advancegold - currentgold > 0){
            noticetext.text = "Get "+ (advancegold - currentgold) + " MORE Golds to Advanced!";
        }
        else{
            noticetext.text = "You can go to Next Level Now!";
            noticetext.color = Color.black;
        }
        
    }
    //public void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    //{
      //  currentgold = 0;
    //}
    public void minushealth(int curammount){
        //currenthealth += minusamount;
        //slider.value = health;
        
        healthtext.text = curammount.ToString();
    }
    public void addgold(int addamount){
        currentgold += addamount;
        if(addamount < 5){
            coinsound.Play();
        }
        else{
            treasuresound.Play();
        }
        FindObjectOfType<coinBar>().setvalue(currentgold);
        goldtext.text = currentgold.ToString();
    }
    public int returngold(){
        return currentgold;
    }
}
