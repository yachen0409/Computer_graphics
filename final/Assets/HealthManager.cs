using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
public class HealthManager : MonoBehaviour
{ 
    public int a = 0;
    public int life = 3;
    public GameObject[] hearts;
    public int currentHealth;
    public int maxHealth;
    public AudioSource ggsound;
    public AudioSource hitsound;
    public AudioSource easyhitsound;
    public AudioSource hitsound2;
    public PlayerController thePlayer;
    public AudioSource welcomesound;
    
    public float invincibilityLength;
    private float invincibilityCounter;
    
    public Renderer playerRenderer;
    private float flashCounter;
    public float flashLength = 0.1f;
    
    private bool isRespawning;
    public Vector3 respawnPoint;
    public float respawnLength;
    
    public GameObject deathEffect;
    public Image blackScreen;
    private bool isFadeToBlack;
    private bool isFadeFromBlack;
    public float fadespeed;
    public float waitForFade;
    private bool firstTimeEnter = true;
    // Start is called before the first frame update
    void Start()
    {
        currentHealth = maxHealth;
        welcomesound.Play();
	//thePlayer = FindObjectOfType<PlayerController>();
	//if(firstTimeEnter){
	    //respawnPoint = thePlayer.transform.position;
	    //firstTimeEnter = false;
	//}
	
    }

    // Update is called once per frame
    void Update()
    {
    
        if(invincibilityCounter > 0){
            invincibilityCounter -= Time.deltaTime;
            flashCounter -= Time.deltaTime;
            if(flashCounter <= 0){
                playerRenderer.enabled = !playerRenderer.enabled;
                flashCounter = flashLength;
            }
            if(invincibilityCounter <= 0){
                playerRenderer.enabled = true;
            }
        }
        if(isFadeToBlack){
            blackScreen.color = new Color(blackScreen.color.r, blackScreen.color.g, blackScreen.color.b, Mathf.MoveTowards(blackScreen.color.a, 1f, fadespeed * Time.deltaTime));
            if(blackScreen.color.a == 1f){
                isFadeToBlack = false;
            }
        }
        if(isFadeFromBlack){
            blackScreen.color = new Color(blackScreen.color.r, blackScreen.color.g, blackScreen.color.b, Mathf.MoveTowards(blackScreen.color.a, 0f, fadespeed * Time.deltaTime));
            if(blackScreen.color.a == 0f){
                isFadeFromBlack = false;
            }
        }
    }
    public void HurtPlayer(int damage, Vector3 direction){
        if(invincibilityCounter <= 0){
    	    currentHealth -= damage;
    	    if(damage <= 2){
    	        easyhitsound.Play();
    	    }
    	    else{
    	        hitsound.Play();
    	        
    	    
    	    }
    	    
    	    hitsound2.Play();
    	    if(currentHealth <= 0){
    	    	Respawn();
    	    	
    	    }
    	    else{
    	        thePlayer.KnockBack(direction);
    	        invincibilityCounter = invincibilityLength;
    	    
    	        playerRenderer.enabled = false;
    	        flashCounter = flashLength;
    	    
    	    }
    	    FindObjectOfType<GameManager>().minushealth(currentHealth);
    	    FindObjectOfType<healthBar>().setHealth(currentHealth);
    	    
    	    
        }
        
        
    }
    public void HealPlayer(int heal){
    	currentHealth += heal;
    	if(currentHealth > maxHealth){
    	    currentHealth = maxHealth;
    	}
    }
    public void Respawn(){
         //thePlayer.transform.position = respawnPoint;
         //currentHealth = maxHealth;
         if(!isRespawning){
             life--;
             hearts[life].GetComponent<Image>().color = new Color32(70, 70, 70, 255);
             StartCoroutine("RespawnCo");
         }
    }
    public IEnumerator RespawnCo(){
        a++;
        ggsound.Play();
    	isRespawning = true;
    	thePlayer.gameObject.SetActive(false);
    	Instantiate(deathEffect, thePlayer.transform.position, thePlayer.transform.rotation);
    	yield return new WaitForSeconds(respawnLength);
    	isFadeToBlack = true;
        yield return new WaitForSeconds(waitForFade);
        thePlayer.transform.position = PlayerController.respawnPoint;
        if(life <= 0){
            SceneManager.LoadScene(5);
        }
        else{
        isFadeFromBlack = true;
    	isRespawning = false;
    	thePlayer.gameObject.SetActive(true);
    	
        currentHealth = maxHealth;
        FindObjectOfType<GameManager>().minushealth(maxHealth);
        FindObjectOfType<healthBar>().setHealth(maxHealth);
        invincibilityCounter = invincibilityLength;
    	    
    	playerRenderer.enabled = false;
    	flashCounter = flashLength;
    	}
    }
}
